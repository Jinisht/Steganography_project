#ifndef DECODE_H
#define DECODE_H


#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4
#define MAX_MAGIC_STR_SIZE 8

#include <stdio.h>
#include "types.h" // Contains user defined types

typedef struct _DecodeInfo
{
    /* stego/default/output Image info */
    char *encoded_image_fname;
    FILE *fptr_encoded_image_fname;
    char extracted_image_data[MAX_IMAGE_BUF_SIZE];
    char decode_image_secret_data[MAX_IMAGE_BUF_SIZE];
    char image_data_bytes[MAX_MAGIC_STR_SIZE];

    /* Secret File Info */
    char *output_secret_fname;
    FILE *fptr_output_secret;
    char secret_file_extn[MAX_FILE_SUFFIX];
    char secret_data[MAX_IMAGE_BUF_SIZE];
    int secret_file_extn_size;
    int secret_file_size;
} DecodeInfo;

/* Read and validate decode file args from argv */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

/* Perform the decoding */
Status do_decoding(DecodeInfo *decInfo);

/* Get File pointers for bmp file */
Status open_files_bmp(DecodeInfo *decInfo);

/* Get File pointers o/p files */
Status open_files_txt(DecodeInfo *decInfo);

/* Decoding and validation of Magic String */
Status decode_magic_string(int size, DecodeInfo *decInfo);

/* extract function, extract data from image */
Status decode_image_to_data(char *data_extract, char *decode_data ,int size, DecodeInfo *decInfo);

/* decode function, decode data from extracted */
Status decode_lsb_to_byte(char *data, char *decoded_bytes);

/* decode function, decode size data from lsb */
Status decode_lsb_to_size(int *size, DecodeInfo *decInfo);

/* decode function, decode file extn data from image */
Status decode_secret_file_extn( DecodeInfo *decInfo);

/* decode function, decode file extn size from image */
Status decode_secret_file_extn_size(DecodeInfo *decInfo);

/* validation function, validate exten and create output file */
Status validate_and_creation_output_file( DecodeInfo *decInfo);

/* decode function, decode file size data from image */
Status decode_secret_file_size(DecodeInfo *decInfo);

/* decode function, decode file secret data from image */
Status decode_secret_file_data(DecodeInfo *decInfo);

#endif