import flask
from werkzeug.utils import secure_filename
import os
import cv2
import numpy as np
from PIL import Image
import io
import base64

app = Flask(__name__)

UPLOAD_FOLDER = 'uploads'
SHUTTER_FOLDER = 'shutters'
ALLOWED_EXTENSIONS = {'png', 'jpg', 'jpeg'}

app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
app.config['SHUTTER_FOLDER'] = SHUTTER_FOLDER
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024  # 16MB max upload size


class ShutterStyle:
    def __init__(self, name, image_path):
        self.name = name
        self.image = Image.open(image_path)


def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS


def load_shutter_styles():
    styles = {}
    for filename in os.listdir(app.config['SHUTTER_FOLDER']):
        if filename.endswith(('.png', '.jpg', '.jpeg')):
            name = os.path.splitext(filename)[0]
            path = os.path.join(app.config['SHUTTER_FOLDER'], filename)
            styles[name] = ShutterStyle(name, path)
    return styles


def detect_windows(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (5, 5), 0)
    edges = cv2.Canny(blurred, 50, 150)
    dilated = cv2.dilate(edges, None, iterations=2)
    contours, _ = cv2.findContours(dilated.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    contours = sorted(contours, key=cv2.contourArea, reverse=True)

    windows = []
    for contour in contours:
        peri = cv2.arcLength(contour, True)
        approx = cv2.approxPolyDP(contour, 0.02 * peri, True)

        if len(approx) == 4:
            x, y, w, h = cv2.boundingRect(approx)
            aspect_ratio = w / float(h)

            if 0.5 <= aspect_ratio <= 2.0 and 1000 < w * h < 100000:
                windows.append((x, y, w, h))

    return windows


def draw_shutter(image, x, y, width, height, style):
    shutter_img = style.image.copy()
    shutter_img = shutter_img.resize((width, height), Image.LANCZOS)

    if shutter_img.mode != 'RGBA':
        shutter_img = shutter_img.convert('RGBA')

    shutter_area = Image.new('RGBA', (width, height), (0, 0, 0, 0))
    shutter_area.paste(shutter_img, (0, 0), shutter_img)

    image = image.convert('RGBA')
    image.paste(shutter_area, (x, y), shutter_area)

    return image


def apply_shutters(image, windows, style):
    for window in windows:
        x, y, w, h = window
        shutter_width = int(w * 0.2)

        image = draw_shutter(image, x - shutter_width, y, shutter_width, h, style)
        image = draw_shutter(image, x + w, y, shutter_width, h, style)

    return image


@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        if 'file' not in request.files:
            return jsonify({'error': 'No file part'}), 400
        file = request.files['file']
        if file.filename == '':
            return jsonify({'error': 'No selected file'}), 400
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file_path = os.path.join(app.config['UPLOAD_FOLDER'], filename)
            file.save(file_path)
            return jsonify({'filename': filename}), 200
    return render_template('upload.html')


@app.route('/process', methods=['POST'])
def process_image():
    data = request.json
    filename = data['filename']
    style_name s = data['style']

    file_path: LiteralString | str | bytes = os.path.join(app.config['UPLOAD_FOLDER'], filename)
    image = cv2.imread(file_path)
    windows = detect_windows(image)

    styles = load_shutter_styles()
    if style_name not in styles:
        return jsonify({'error': 'Invalid style'}), 400

    image_pil = Image.fromarray(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
    processed_image = apply_shutters(image_pil, windows, styles[style_name])

    buffered = io.BytesIO()
    processed_image.save(buffered, format="PNG")
    img_str = base64.b64encode(buffered.getvalue()).decode()

    return jsonify({'image': img_str}), 200


@app.route('/styles')
def get_styles():
    styles = load_shutter_styles()
    return jsonify({'styles': list(styles.keys())}), 200


if __name__ == '__main__':
    os.makedirs(app.config['UPLOAD_FOLDER'], exist_ok=True)
    os.makedirs(app.config['SHUTTER_FOLDER'], exist_ok=True)
    app.run(debug=True)
