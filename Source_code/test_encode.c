#include <stdio.h>
#include "encode.h"
#include "decode.h"
#include "types.h"
#include <string.h>

int main(int argc, char *argv[])
{
    //validate cla
    EncodeInfo E1;
    DecodeInfo D1;
    int choice = check_operation_type(argv);
    if (choice ==e_encode){
        printf("Encoding is selected\n");
        if ((read_and_validate_encode_args(argv, &E1 )) == e_success){
            printf("INFO : Read and validate is sucess\n");
            if (do_encoding(&E1)==e_success){
                printf("Encoding is success\n ");
            }
            else{
                printf("Failed to encode\n");
                return 0;
            }

        }
        else{
            printf("INFO : Failed to read and validate encode args\n");
            return 0;
        }
    }
    else if (choice ==e_decode){
        printf("Decoding is selected\n");
        if (read_and_validate_decode_args(argv, &D1) == e_success){
             printf("INFO : Read and validate bmp file is success\n");
             if (do_decoding(&D1) ==e_success){
                printf("Decoding is success\n ");
             }
             else{
                printf("Failed to decode\n");
                return 0;
             }
        }
        else{
            printf("INFO : Failed to read and validate bmp file args\n");
            return 0;
        }
    }
    else if (choice ==e_unsupported){
        printf("Invalid operation\nUsage:\n");
        printf("For Encoding : ./a.out -e beautiful.bmp secret.txt stego.bmp\n");
        printf("For Decoding : ./a.out -d stego.bmp output.txt\n");
    }

    return 0;
}

OperationType check_operation_type(char *argv[]){

    if(strcmp(argv[1], "-e")==0){
        return e_encode;
    }
    else if(strcmp(argv[1], "-d")== 0){
        return e_decode;
    }
    else{
        return e_unsupported;
    }
}

