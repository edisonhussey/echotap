import os

# Define the path (escaping the space with backslash or using raw string)
usb_path = "/Volumes/usb/edison"

# Define your sentence
sentence = "This is the sentence I want to write to the file."

# Ensure the destination directory exists
os.makedirs(usb_path, exist_ok=True)

# Define the full file path
file_path = os.path.join(usb_path, "kk.txt")

# Write the sentence to the file
try:
    with open(file_path, "w") as file:
        file.write(sentence)
    print(f"Successfully wrote to {file_path}")
except Exception as e:
    print(f"Failed to write to file: {e}")
