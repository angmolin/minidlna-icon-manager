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
#define MAX_LINE_LEN 24

int main(int argc, char **argv) {
    printf("### MiniDLNA Icon Embeder ###\n\n");

    if (argc != 3) {
        printf("Usage: %s <input-file> <output-file>\n", argv[0]);

        return 1;
    }

    printf("    Input file: %s\n", argv[1]);
    printf("    Output file: %s\n\n", argv[2]);

    FILE *in_fd;
    in_fd = fopen(argv[1], "rb");
    printf("Opening input file...");

    if (in_fd == NULL) {
        printf("[ ERROR ]\n");

        return 1;
    }
    printf("[  OK   ]\n");

    printf("Reading input file...\n");

    size_t i = 0, j = 0, len = MALLOC_BLOCK_SIZE;
    char *bytes = malloc(sizeof(char) * len);

    if (bytes == NULL) {
        printf("Error allocating memory. Exiting...\n");
        return 1;
    }

    while ((j = fread(bytes + i, sizeof(char), MALLOC_BLOCK_SIZE, in_fd)) == MALLOC_BLOCK_SIZE) {
        i += j;
        printf("+ %zd\n", len);

        len += MALLOC_BLOCK_SIZE;
        bytes = realloc(bytes, len);

        if (bytes == NULL) {
            printf("Error reallocating memory. Exiting...\n");
            return 1;
        }
    }
    i += j;
    
    printf("= %zd\n", i);
    printf("Ok!\n");

    FILE *out_fd;
    out_fd = fopen(argv[2], "w");
    printf("Opening output file...");

    if (out_fd == NULL) {
        printf("[ ERROR ]\n");

        return 1;
    }
    printf("[  OK   ]\n");

    printf("Writing output file...\n");
    printf("%zd values\n", i);


    fprintf(out_fd, "\"");
    for (j = 0; j < i; j++) {
        fprintf(out_fd, "\\x%02x", bytes[j] & 0xFF);
        
        if ((j + 1) % MAX_LINE_LEN == 0) {
            fprintf(out_fd, "\"\n\"");
        }
    }
    fprintf(out_fd, "\"");

    printf("Memory freeing...");
    free(bytes);
    printf("[  OK   ]\n");

    return 0;
}