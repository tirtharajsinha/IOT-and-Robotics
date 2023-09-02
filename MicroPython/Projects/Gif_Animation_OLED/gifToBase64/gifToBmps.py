from os import listdir, mkdir, getcwd, path, removedirs
from PIL import Image

OUTPUT_SIZE = (
    64,
    64,
)  # The output size of each frame (or tile or Sprite) of the animation
MONOCHROME = True  # Do you want the output file to be b/w?

for file in listdir():
    if file.endswith(".gif"):
        gif = Image.open(file)
        print(f"Size: {gif.size}")
        print(f"Frames: {gif.n_frames}")
        giffilename = file.replace(".gif", "")
        # if MONOCHROME:
        #     output = Image.new("1", (OUTPUT_SIZE[0] * gif.n_frames, OUTPUT_SIZE[1]), 0)
        # else:
        #     output = Image.new("RGB", (OUTPUT_SIZE[0] * gif.n_frames, OUTPUT_SIZE[1]))

        outputfolder = path.join(getcwd(), f"{giffilename}_{gif.n_frames}Frames")

        if path.exists(outputfolder):
            removedirs(outputfolder)
        mkdir(outputfolder)

        for frame in range(0, gif.n_frames):
            output_filename = path.join(outputfolder, f"frame_{frame}.bmp")
            gif.seek(frame)
            extracted_frame = gif.resize(OUTPUT_SIZE)
            if not MONOCHROME:
                extracted_frame = extracted_frame.convert("P", colors=8)
            extracted_frame.save(output_filename)
