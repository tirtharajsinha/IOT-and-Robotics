from os import listdir
from PIL import Image

OUTPUT_SIZE = (
    128,
    64,
)  # The output size of each frame (or tile or Sprite) of the animation
MONOCHROME = True  # Do you want the output file to be b/w?

for file in listdir():
    if file.endswith(".png"):
        gif = Image.open(file)
        output_filename = f"icon_{gif.n_frames}_frames.bmp"
        extracted_frame = gif.resize(OUTPUT_SIZE)
        fn = lambda x: 255 if x > 65 else 0
        r = extracted_frame.convert("L").point(fn, mode="1")
        r.save(output_filename)
