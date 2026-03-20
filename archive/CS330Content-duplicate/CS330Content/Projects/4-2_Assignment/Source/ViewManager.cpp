///////////////////////////////////////////////////////////////////////////////
// viewmanager.cpp
// ============
// Manage the viewing of 3D objects within the viewport with interactive
// camera controls
//
// CAMERA CONTROL SYSTEM:
//
// Keyboard Controls:
//   W/S - Forward/Backward movement along camera's front vector
//   A/D - Left/Right strafing along camera's right vector
//   Q/E - Up/Down movement along world up vector
//   ESC - Exit application
//
// Mouse Controls:
//   Movement - Rotate camera view (yaw and pitch)
//   Scroll   - Adjust movement speed (0.1 to 45.0 range)
//
// Technical Implementation:
//   - Uses Euler angles (yaw/pitch) for camera orientation
//   - Delta time ensures frame-independent movement
//   - Perspective projection with adjustable FOV (zoom)
//   - View matrix built with glm::lookAt()
//
//  AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, Nov. 1st, 2023
//  Modified: Camera controls implementation
///////////////////////////////////////////////////////////////////////////////

#include "ViewManager.h"

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>    

// declaration of the global variables and defines
namespace
{
	// Variables for window width and height
	const int WINDOW_WIDTH = 1000;
	const int WINDOW_HEIGHT = 800;
	const char* g_ViewName = "view";
	const char* g_ProjectionName = "projection";

	// camera object used for viewing and interacting with
	// the 3D scene
	Camera* g_pCamera = nullptr;

	// these variables are used for mouse movement processing
	float gLastX = WINDOW_WIDTH / 2.0f;
	float gLastY = WINDOW_HEIGHT / 2.0f;
	bool gFirstMouse = true;

	// time between current frame and last frame
	float gDeltaTime = 0.0f; 
	float gLastFrame = 0.0f;

	// if orthographic projection is on, this value will be
	// true
	bool bOrthographicProjection = false;
}

/***********************************************************
 *  ViewManager()
 *
 *  The constructor for the class
 ***********************************************************/
ViewManager::ViewManager(
	ShaderManager *pShaderManager)
{
	// initialize the member variables
	m_pShaderManager = pShaderManager;
	m_pWindow = NULL;
	g_pCamera = new Camera();
	// default camera view parameters
	g_pCamera->Position = glm::vec3(0.5f, 5.5f, 10.0f);
	g_pCamera->Front = glm::vec3(0.0f, -0.5f, -2.0f);
	g_pCamera->Up = glm::vec3(0.0f, 1.0f, 0.0f);
	g_pCamera->Zoom = 80;
}

/***********************************************************
 *  ~ViewManager()
 *
 *  The destructor for the class
 ***********************************************************/
ViewManager::~ViewManager()
{
	// free up allocated memory
	m_pShaderManager = NULL;
	m_pWindow = NULL;
	if (NULL != g_pCamera)
	{
		delete g_pCamera;
		g_pCamera = NULL;
	}
}

/***********************************************************
 *  CreateDisplayWindow()
 *
 *  This method is used to create the main display window.
 ***********************************************************/
GLFWwindow* ViewManager::CreateDisplayWindow(const char* windowTitle)
{
	GLFWwindow* window = nullptr;

	// try to create the displayed OpenGL window
	window = glfwCreateWindow(
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		windowTitle,
		NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);

	// this callback is used to receive mouse moving events
	glfwSetCursorPosCallback(window, &ViewManager::Mouse_Position_Callback);

	// this callback is used to receive mouse scroll wheel events
	glfwSetScrollCallback(window, &ViewManager::Mouse_Scroll_Callback);

	// tell GLFW to capture all mouse events and hide the cursor for FPS-style camera control
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// enable blending for supporting tranparent rendering
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_pWindow = window;

	return(window);
}

/***********************************************************
 *  Mouse_Position_Callback()
 *
 *  This method is automatically called from GLFW whenever
 *  the mouse is moved within the active GLFW display window.
 *
 *  Camera Orientation Control:
 *  - Mouse horizontal movement (X) controls camera yaw (left/right rotation)
 *  - Mouse vertical movement (Y) controls camera pitch (up/down rotation)
 *  - Pitch is constrained between -89° and 89° to prevent gimbal lock
 *
 *  Math Behind Orientation:
 *  1. Calculate offset from last mouse position
 *  2. Apply mouse sensitivity to offsets
 *  3. Update yaw and pitch angles
 *  4. Convert Euler angles to direction vector:
 *     front.x = cos(yaw) * cos(pitch)
 *     front.y = sin(pitch)
 *     front.z = sin(yaw) * cos(pitch)
 *  5. Recalculate Right and Up vectors using cross products
 ***********************************************************/
void ViewManager::Mouse_Position_Callback(GLFWwindow* window, double xMousePos, double yMousePos)
{
	// when the first mouse move event is received, initialize last position
	// to prevent camera jump on first movement
	if (gFirstMouse)
	{
		gLastX = xMousePos;
		gLastY = yMousePos;
		gFirstMouse = false;
	}

	// calculate the X and Y offset values from the last mouse position
	float xOffset = xMousePos - gLastX;
	float yOffset = gLastY - yMousePos; // reversed since y-coordinates go from bottom to top

	// store current position for next frame's offset calculation
	gLastX = xMousePos;
	gLastY = yMousePos;

	// update camera orientation based on mouse movement
	// ProcessMouseMovement applies sensitivity, updates yaw/pitch, and recalculates camera vectors
	g_pCamera->ProcessMouseMovement(xOffset, yOffset);
}

/***********************************************************
 *  Mouse_Scroll_Callback()
 *
 *  This method is automatically called from GLFW whenever
 *  the mouse scroll wheel is used within the active GLFW
 *  display window.
 ***********************************************************/
void ViewManager::Mouse_Scroll_Callback(GLFWwindow* window, double xOffset, double yOffset)
{
	// adjust the camera movement speed based on scroll wheel input
	// positive yOffset (scroll up) decreases speed, negative (scroll down) increases speed
	// the ProcessMouseScroll method handles speed boundaries (min: 0.1f, max: 45.0f)
	if (g_pCamera)
	{
		g_pCamera->ProcessMouseScroll(yOffset);
	}
}

/***********************************************************
 *  ProcessKeyboardEvents()
 *
 *  This method is called to process any keyboard events
 *  that may be waiting in the event queue.
 *
 *  Camera Movement Controls:
 *  - W: Move forward in the direction camera is facing
 *  - S: Move backward opposite to camera direction
 *  - A: Move left (strafe) perpendicular to camera direction
 *  - D: Move right (strafe) perpendicular to camera direction
 *  - Q: Move up along the world Up vector
 *  - E: Move down along the world Up vector
 *  - ESC: Close the application window
 *
 *  Movement uses delta time for frame-independent speed,
 *  ensuring consistent movement regardless of frame rate.
 ***********************************************************/
void ViewManager::ProcessKeyboardEvents()
{
	// close the window if the escape key has been pressed
	if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_pWindow, true);
	}

	// if the camera object is null, then exit this method
	if (NULL == g_pCamera)
	{
		return;
	}

	// process camera forward/backward movement
	// W key: move forward (camera position += front * speed * deltaTime)
	if (glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		g_pCamera->ProcessKeyboard(FORWARD, gDeltaTime);
	}
	// S key: move backward (camera position -= front * speed * deltaTime)
	if (glfwGetKey(m_pWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		g_pCamera->ProcessKeyboard(BACKWARD, gDeltaTime);
	}

	// process camera left/right strafing movement
	// A key: move left (camera position -= right * speed * deltaTime)
	if (glfwGetKey(m_pWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		g_pCamera->ProcessKeyboard(LEFT, gDeltaTime);
	}
	// D key: move right (camera position += right * speed * deltaTime)
	if (glfwGetKey(m_pWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		g_pCamera->ProcessKeyboard(RIGHT, gDeltaTime);
	}

	// process camera vertical movement (up and down)
	// Q key: move up (camera position += up * speed * deltaTime)
	if (glfwGetKey(m_pWindow, GLFW_KEY_Q) == GLFW_PRESS)
	{
		g_pCamera->ProcessKeyboard(UP, gDeltaTime);
	}
	// E key: move down (camera position -= up * speed * deltaTime)
	if (glfwGetKey(m_pWindow, GLFW_KEY_E) == GLFW_PRESS)
	{
		g_pCamera->ProcessKeyboard(DOWN, gDeltaTime);
	}
}

/***********************************************************
 *  PrepareSceneView()
 *
 *  This method is called every frame to update the camera
 *  view and projection matrices before rendering the 3D scene.
 *
 *  Render Loop Flow:
 *  1. Calculate delta time (time between frames) for smooth,
 *     frame-independent movement
 *  2. Process keyboard input for camera movement
 *  3. Get updated view matrix from camera using lookAt()
 *  4. Calculate perspective projection matrix
 *  5. Send matrices to shaders for 3D to 2D transformation
 *
 *  View Matrix: Transforms world space to camera space
 *    - Built using glm::lookAt(position, target, up)
 *    - Updated by mouse movement (yaw/pitch) and keyboard
 *
 *  Projection Matrix: Transforms camera space to clip space
 *    - Uses perspective projection with camera's zoom (FOV)
 *    - Aspect ratio based on window dimensions
 *    - Near plane: 0.1f, Far plane: 100.0f
 ***********************************************************/
void ViewManager::PrepareSceneView()
{
	glm::mat4 view;
	glm::mat4 projection;

	// calculate delta time for frame-independent movement
	// delta time = time elapsed since last frame
	float currentFrame = glfwGetTime();
	gDeltaTime = currentFrame - gLastFrame;
	gLastFrame = currentFrame;

	// process any keyboard events that may be waiting in the
	// event queue (WASD, QE movement keys)
	ProcessKeyboardEvents();

	// get the current view matrix from the camera
	// view matrix = lookAt(cameraPos, cameraPos + cameraFront, cameraUp)
	view = g_pCamera->GetViewMatrix();

	// define the current projection matrix using perspective projection
	// parameters: FOV (zoom), aspect ratio, near plane, far plane
	projection = glm::perspective(glm::radians(g_pCamera->Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

	// if the shader manager object is valid
	if (NULL != m_pShaderManager)
	{
		// set the view matrix into the shader for proper rendering
		m_pShaderManager->setMat4Value(g_ViewName, view);
		// set the projection matrix into the shader for proper rendering
		m_pShaderManager->setMat4Value(g_ProjectionName, projection);
		// set the view position of the camera into the shader for proper rendering
		m_pShaderManager->setVec3Value("viewPosition", g_pCamera->Position);
	}
}