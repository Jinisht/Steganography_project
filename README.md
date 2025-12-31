# Steganography_project
This steganography project is an application that implements data hiding in image files by encoding secret information into the image and extracting the embedded data through a decoding process.


Steganography Project in C

This project implements image steganography using the C programming language, allowing confidential information to be securely hidden within digital images. The application embeds secret text data into a BMP image by modifying the Least Significant Bits (LSB) of pixel values, ensuring that the visual quality of the image remains unchanged to the human eye.

The program supports both encoding and decoding operations. During encoding, the user provides a source image and a secret message, which is then embedded into the image and saved as a stego image. During decoding, the hidden message is extracted from the stego image and displayed to the user.

The project demonstrates core concepts of file handling, bitwise operations, data security, and low-level memory manipulation in C. It highlights how steganography can be used as an additional layer of security alongside cryptographic techniques for secure communication.
