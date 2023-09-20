def convert_bmp_to_bytearray(filename):
  with open(filename, "rb") as f:
    contents = f.read()
  header_size = 14
  byte_array = contents[header_size:]
  return bytearray(byte_array)