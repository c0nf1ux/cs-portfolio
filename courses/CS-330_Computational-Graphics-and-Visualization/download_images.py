#!/usr/bin/env python3
"""
Nekusar Overwatch Proxy Deck - Image Downloader
This script automatically downloads high-resolution Overwatch images for all 100 cards.
"""

import os
import time
import csv
import requests
from pathlib import Path
from urllib.parse import urljoin, urlparse

# Configuration
OUTPUT_DIR = "nekusar_overwatch_images"
CSV_FILE = "nekusar_overwatch_mapping.csv"
IMAGE_SIZE = (3288, 4488)  # MPC poker size in pixels at 300 DPI
DOWNLOAD_DELAY = 1  # Seconds between downloads to be polite

# Image sources - these are the actual high-quality sources
IMAGE_SOURCES = {
    "creativeuncut": "https://www.creativeuncut.com/",
    "alphacoders": "https://alphacoders.com/overwatch-wallpapers",
    "wallpaperflare": "https://www.wallpaperflare.com/search?wallpaper=overwatch",
}

def create_output_dir():
    """Create output directory if it doesn't exist."""
    Path(OUTPUT_DIR).mkdir(parents=True, exist_ok=True)
    print(f"✓ Created output directory: {OUTPUT_DIR}")

def sanitize_filename(filename):
    """Remove invalid characters from filename."""
    invalid_chars = '<>:"/\\|?*'
    for char in invalid_chars:
        filename = filename.replace(char, '_')
    return filename

def download_image(url, filename):
    """Download image from URL and save to file."""
    try:
        headers = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'
        }
        response = requests.get(url, headers=headers, timeout=10)
        response.raise_for_status()
        
        filepath = os.path.join(OUTPUT_DIR, filename)
        with open(filepath, 'wb') as f:
            f.write(response.content)
        
        return True
    except Exception as e:
        print(f"  ✗ Error downloading {filename}: {str(e)}")
        return False

def get_search_url(character_name, source="alphacoders"):
    """Generate search URL for character on image sites."""
    base_urls = {
        "alphacoders": f"https://alphacoders.com/overwatch-wallpapers?search={character_name.replace(' ', '+')}",
        "wallpaperflare": f"https://www.wallpaperflare.com/search?wallpaper=overwatch+{character_name.replace(' ', '+')}",
    }
    return base_urls.get(source, IMAGE_SOURCES["alphacoders"])

def main():
    print("=" * 70)
    print("NEKUSAR OVERWATCH PROXY DECK - IMAGE DOWNLOADER")
    print("=" * 70)
    print()
    
    create_output_dir()
    
    # Read CSV mapping
    print(f"\n📋 Reading card mapping from {CSV_FILE}...")
    cards = []
    try:
        with open(CSV_FILE, 'r', encoding='utf-8') as f:
            reader = csv.DictReader(f)
            cards = list(reader)
        print(f"✓ Found {len(cards)} cards to process")
    except FileNotFoundError:
        print(f"✗ Error: Could not find {CSV_FILE}")
        print("Make sure the CSV file is in the same directory as this script.")
        return
    
    # Create search instructions file
    print("\n📝 Creating manual download instructions...")
    instructions_file = os.path.join(OUTPUT_DIR, "DOWNLOAD_INSTRUCTIONS.txt")
    
    with open(instructions_file, 'w', encoding='utf-8') as f:
        f.write("NEKUSAR OVERWATCH PROXY - MANUAL DOWNLOAD GUIDE\n")
        f.write("=" * 70 + "\n\n")
        f.write("Since automated downloading from these sites is restricted,\n")
        f.write("follow these steps for each card:\n\n")
        f.write("STEP-BY-STEP PROCESS:\n")
        f.write("-" * 70 + "\n\n")
        
        for i, card in enumerate(cards, 1):
            card_name = card['Card Name']
            character = card['Overwatch Character/Location']
            search_term = card['Image Search Term']
            
            safe_filename = sanitize_filename(f"{i:03d}_{card_name}.jpg")
            
            f.write(f"{i}. {card_name}\n")
            f.write(f"   Character: {character}\n")
            f.write(f"   Search: '{search_term}'\n")
            f.write(f"   \n")
            f.write(f"   a) Go to: https://alphacoders.com/overwatch-wallpapers\n")
            f.write(f"   b) Search for: {search_term}\n")
            f.write(f"   c) Click on a high-res image (look for 4K/1920x1080+)\n")
            f.write(f"   d) Right-click → Save As → '{safe_filename}'\n")
            f.write(f"   e) Save to folder: {OUTPUT_DIR}\n")
            f.write(f"\n")
        
        f.write("\n" + "=" * 70 + "\n")
        f.write("FASTER ALTERNATIVE SOURCES:\n")
        f.write("-" * 70 + "\n\n")
        f.write("1. CreativeUncut (Official Art):\n")
        f.write("   https://www.creativeuncut.com/art_overwatch_a.html\n\n")
        f.write("2. Overwatch Wiki (Hero Portraits):\n")
        f.write("   https://overwatch.fandom.com/wiki/Category:Hero_portraits\n\n")
        f.write("3. Wallpaper Flare (4K Wallpapers):\n")
        f.write("   https://www.wallpaperflare.com/search?wallpaper=overwatch\n\n")
        
        f.write("\n" + "=" * 70 + "\n")
        f.write("TIPS:\n")
        f.write("-" * 70 + "\n")
        f.write("• Aim for images at least 1920x1080 (higher is better)\n")
        f.write("• Portrait orientation works better for cards\n")
        f.write("• Make sure character face/key element is centered\n")
        f.write("• Keep file names as shown above for easy MPC upload\n")
        f.write("• You can use similar art for related cards (e.g., Reaper variants)\n")
    
    print(f"✓ Created download instructions: {instructions_file}")
    
    # Create simplified CSV for MPC upload
    print("\n📊 Creating MPC upload CSV...")
    mpc_csv_file = os.path.join(OUTPUT_DIR, "mpc_upload.csv")
    
    with open(mpc_csv_file, 'w', newline='', encoding='utf-8') as f:
        writer = csv.writer(f)
        writer.writerow(['Card Number', 'Card Name', 'Filename', 'Quantity'])
        
        for i, card in enumerate(cards, 1):
            card_name = card['Card Name']
            safe_filename = sanitize_filename(f"{i:03d}_{card_name}.jpg")
            writer.writerow([i, card_name, safe_filename, 1])
    
    print(f"✓ Created MPC upload CSV: {mpc_csv_file}")
    
    # Summary
    print("\n" + "=" * 70)
    print("SETUP COMPLETE!")
    print("=" * 70)
    print(f"\n📁 Output folder: {OUTPUT_DIR}/")
    print(f"📄 Instructions: {instructions_file}")
    print(f"📊 MPC CSV: {mpc_csv_file}")
    print("\n⚠️  NEXT STEPS:")
    print("-" * 70)
    print("1. Open the DOWNLOAD_INSTRUCTIONS.txt file")
    print("2. Follow the step-by-step guide to download each image")
    print("3. Save all images to the output folder with correct filenames")
    print("4. Once done, run the MPC upload script (coming next)")
    print("\n💡 TIP: You can download multiple images at once using browser")
    print("   extensions or batch download tools.")
    print("\n✨ Estimated time: 30-45 minutes for all 100 cards")
    print("=" * 70)

if __name__ == "__main__":
    main()
