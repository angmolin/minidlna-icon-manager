/**
 * Wednesday, June 16, 2021
 * A<3J
 * 
 * Copyright ©2021. Ángel Molina Núñez. All Rights Reserved.
 * Contact angelmolinu@gmail.com for commercial licensing
 * opportunities.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION)
 * 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>

#define MALLOC_BLOCK_SIZE 128

int main(int argc, char **argv) {
    printf("### MiniDLNA Icon Extractor ###\n\n");

    if (argc != 3) {
        printf("Usage: %s <input-file> <output-file>\n", argv[0]);

        return 1;
    }

    printf("    Input file: %s\n", argv[1]);
    printf("    Output file: %s\n\n", argv[2]);

    FILE *in_fd;
    in_fd = fopen(argv[1], "r");
    printf("Opening input file...");

    if (in_fd == NULL) {
        printf("[ ERROR ]\n");

        return 1;
    }
    printf("[  OK   ]\n");

    printf("Reading input file...\n");

    int finished = 0;
    char aux;

    size_t i = 0, len = MALLOC_BLOCK_SIZE;
    char *bytes = malloc(sizeof(char) * len);

    if (bytes == NULL) {
        printf("Error allocating memory. Exiting...\n");
        return 1;
    }

    while (!finished) {
        if (fscanf(in_fd, "\\x%x", bytes + i) > 0) {
            i++;

            if (i == len) {
                printf("+ %zd\n", len);

                len += MALLOC_BLOCK_SIZE;
                bytes = realloc(bytes, len);

                if (bytes == NULL) {
                    printf("Error reallocating memory. Exiting...\n");
                    return 1;
                }
            }
        }
        else {
            aux = getc(in_fd);

            if (aux == EOF) {
                finished = 1;
            }
        }
    }
    i--;

    printf("= %zd\n", i);
    printf("Ok!\n");

    FILE *out_fd;
    out_fd = fopen(argv[2], "wb");
    printf("Opening output file...");

    if (out_fd == NULL) {
        printf("[ ERROR ]\n");

        return 1;
    }
    printf("[  OK   ]\n");

    printf("Writing output file...\n");
    printf("%zd bytes\n", i);
    fwrite(bytes, sizeof(char), i, out_fd);

    printf("Memory freeing...");
    free(bytes);
    printf("[  OK   ]\n");

    return 0;
}