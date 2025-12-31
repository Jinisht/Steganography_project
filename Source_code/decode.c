/*Description:decoding secret data from .bmp file
Date:21-12-2025
Name:Jinish Thomas
Sample i/p: .bmp file
Sample o/p: .txt file with secret data
*/

#include <stdio.h>
#include "decode.h"
#include "types.h"
#include <string.h>
#include "common.h"

/* Function Definitions */

/* Get encoded data from image by decoding
 * Input: Encoded Image file ptr
 * Output: Txt file with decoded data from image
 * Description: Data is stored in Bmp image, decoded data should write in a text file.
 */

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo){
    if((strstr(argv[2], ".bmp")) != NULL){
        decInfo->encoded_image_fname = argv[2];
    }
    else{
        return e_failure;
    }

    if(strstr(argv[2], ".txt")!= NULL){
        decInfo->output_secret_fname = argv[3];
    }
    else{
        decInfo->output_secret_fname = "output.txt";
        //printf("output txt is created\n");
    }
return e_success;
}

Status open_files_bmp(DecodeInfo *decInfo)
{
    // default(encoded) Image file
    decInfo->fptr_encoded_image_fname = fopen(decInfo->encoded_image_fname, "r");
    // Do Error handling
    if (decInfo->fptr_encoded_image_fname == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->encoded_image_fname);

    	return e_failure;
    }
    // No failure return e_success
return e_success;
}

Status open_files_txt(DecodeInfo *decInfo){
    decInfo->fptr_output_secret = fopen(decInfo->output_secret_fname, "w");
        // Do Error handling
        if (decInfo->fptr_output_secret == NULL){
            perror("fopen");
            fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->output_secret_fname);

        return e_failure;
        }
        // No failure return e_success
return e_success;

}
Status decode_lsb_to_byte(char *data, char *decoded_bytes){
    //*decoded_bytes = 0;
    for(int i=0; i<8; i++){
        decoded_bytes[i] = 0;
        *decoded_bytes = *decoded_bytes | (data[i] & 1) << i; //get bit from lsb side of data       
    }  
//printf("%s\n",decoded_bytes);
return e_success;
}

Status decode_image_to_data(char *data_extract, char *decode_data ,int size, DecodeInfo *decInfo){
    //decInfo->extracted_image_data[size] = '\0';
    for (int i=0; i<size; i++){
        fread(data_extract, 8, 1, decInfo->fptr_encoded_image_fname);
        decode_lsb_to_byte(data_extract, &decode_data[i]);       
    }
return e_success;
}

Status decode_magic_string(int size, DecodeInfo *decInfo){
    fseek(decInfo->fptr_encoded_image_fname, 54, SEEK_SET);
    decode_image_to_data(decInfo->image_data_bytes, decInfo->extracted_image_data, size, decInfo);
    
    // validate magic string
    if (strcmp(decInfo->extracted_image_data, MAGIC_STRING) == 0){
        
        printf("Magic string is decoded and validated\n");
    }
    else{
        printf("Failed to validate the magic string\n");
    }

return e_success;
}

Status decode_lsb_to_size(int *size, DecodeInfo *decInfo){
    char str[32];
    *size=0;
    fread(str, 32, 1 ,decInfo->fptr_encoded_image_fname);
    // Size - 32 bit - 32 bytes (str)
    for(int i=0; i < 32; i++){
        *size = *size | (str[i] & 1) << i; //get bit from lsb side of data
    }
   //  printf("%d\n", *size);
return e_success;
}

Status decode_secret_file_extn_size(DecodeInfo *decInfo){
    decode_lsb_to_size(&decInfo->secret_file_extn_size, decInfo);
    return e_success;
}

Status decode_secret_file_extn( DecodeInfo *decInfo){
    decode_image_to_data(decInfo->image_data_bytes, decInfo->secret_file_extn, decInfo->secret_file_extn_size, decInfo);
return e_success;
}

Status validate_and_creation_output_file( DecodeInfo *decInfo){
    if (strcmp(decInfo->secret_file_extn, ".txt") == 0){
        printf("File extension validated successfully\n");
        if (strstr(decInfo->output_secret_fname,".txt") != 0){
            //printf("Output file name is validated\n");
            open_files_txt(decInfo);
        }
        else{
            return e_failure;
        }      
    }
    else{
        return e_failure;
    }
return e_success;
}

Status decode_secret_file_size(DecodeInfo *decInfo){
    decode_lsb_to_size(&decInfo->secret_file_size, decInfo);
    return e_success;
}

Status decode_secret_file_data(DecodeInfo *decInfo){
    char str[25];
    for (int i=0; i<decInfo->secret_file_size; i++){
        fread(decInfo->secret_data, 8, 1, decInfo->fptr_encoded_image_fname);
        decode_lsb_to_byte(decInfo->secret_data, &str[i]); 
        fwrite(&str[i], 1, 1, decInfo->fptr_output_secret );      
    }
return e_success;
}

Status do_decoding(DecodeInfo *decInfo){
    if (open_files_bmp(decInfo)==e_success){
        printf("Files are opened successfully\n");
        if (decode_magic_string(strlen(MAGIC_STRING), decInfo) == e_success){
            printf("Decoded magic string successfully\n");
            if(decode_secret_file_extn_size(decInfo) == e_success){
                printf("Decoded secret file extn size successfully\n");
                if (decode_secret_file_extn(decInfo) == e_success){
                    printf("Decoded secret file extn successfully\n");
                    if (validate_and_creation_output_file(decInfo) == e_success){
                        printf("Output file is validated\n");
                        if (decode_secret_file_size(decInfo) == e_success){
                            printf("Decoded secret file size successfully\n");
                            if (decode_secret_file_data( decInfo)== e_success){
                                printf("Decoded secret file data successfully\n");
                            }
                            else{
                                printf("Failed to decode secret file data\n");
                            }
                        }
                        else{
                            printf("Failed to decode file size\n");
                        }  
                    }
                    else{
                        printf("Failed to validate Output file\n"); 
                    }
                }  
                else{
                    printf("Failed to decode secret file extn\n");
                }
                
            }
            else{
                 printf("Failed to decode secret file extn size\n");
            }

        }
        else{
            printf("Failed to decode magic string successfully\n");

        }
    }
    else{
        printf("Open file is Failure\n");
        return e_failure;
    }

return e_success;
}