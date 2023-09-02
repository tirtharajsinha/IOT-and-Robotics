import cv2
import numpy
import base64
import convert
import json
from PIL import Image
import os
import time


IMAGEPATH = r"rickroll.gif"
RESOLUTION = (64, 64)


def convert_gif_to_frames(IMAGEPATH):
    ISGIF = True
    filename_without_ext = os.path.splitext(os.path.basename(IMAGEPATH))[0]

    if IMAGEPATH.endswith(".gif"):
        gif = cv2.VideoCapture(IMAGEPATH)
    elif IMAGEPATH.endswith(".jpg") or IMAGEPATH.endswith(".png"):
        gif = cv2.imread(IMAGEPATH)
        ISGIF = False

    # Initialize the frame number and create empty frame list
    frame_num = 0
    frame_list = []

    # Loop until there are frames left
    while True:
        try:
            # Try to read a frame. Okay is a BOOL if there are frames or not
            if ISGIF:
                okay, frame = gif.read()
            else:
                okay, frame = True, gif

            # Break if there are no other frames to read
            if not okay:
                break
            # Grayscalling
            frame = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)

            # Resizing
            imgresize = cv2.resize(frame, RESOLUTION)

            _, imgthresh = cv2.threshold(imgresize, 200, 255, cv2.THRESH_BINARY)

            PilImage = Image.fromarray(imgthresh)

            encoded = convert.doStuff(PilImage)

            encoded = encoded.decode("utf-8")
            # Append to empty frame list
            frame_list.append(encoded)

            # Increment value of the frame number by 1
            frame_num += 1

            if not ISGIF:
                break
        except KeyboardInterrupt:  # press ^C to quit
            break

    with open(f"{filename_without_ext}_{frame_num}Frames.json", "w") as f:
        json.dump(frame_list, f)
    return frame_list


frames = convert_gif_to_frames(IMAGEPATH)
print(len(frames))
