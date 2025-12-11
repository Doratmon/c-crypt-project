/*
 * Copyright 2025 Doratmon
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void print_usage(const char *prog)
{
    fprintf(stderr,
            "Usage: %s -k key [-e|-d] [-i infile] [-o outfile]\n"
            "  -k key     : xor key (required)\n"
            "  -e         : encrypt (default behavior)\n"
            "  -d         : decrypt (same as encrypt for XOR)\n"
            "  -i infile  : input file (default stdin)\n"
            "  -o outfile : output file (default stdout)\n",
            prog);
}

/*
 * xor_stream: 从输入读取数据，用重复的密钥进行异或处理后写入输出。
 * 成功返回 0，发生错误返回非零。
 */
static int xor_stream(FILE *in, FILE *out, const unsigned char *key, size_t keylen)
{
    if (!in || !out || !key || keylen == 0) return -1;
    unsigned char buf[4096];
    size_t off = 0;
    while (1) {
        size_t r = fread(buf, 1, sizeof(buf), in);
        if (r == 0) break;
        for (size_t i = 0; i < r; ++i) {
            buf[i] ^= key[(off + i) % keylen];
        }
        off += r;
        if (fwrite(buf, 1, r, out) != r) return -1;
    }
    if (ferror(in) || ferror(out)) return -1;
    return 0;
}

int main(int argc, char **argv)
{
    int opt;
    const char *key = NULL;
    const char *infile = NULL;
    const char *outfile = NULL;
    int mode_encrypt = 1; /* XOR 异或是对称的 */

    while ((opt = getopt(argc, argv, "k:i:o:edh")) != -1) {
        switch (opt) {
        case 'k': key = optarg; break;
        case 'i': infile = optarg; break;
        case 'o': outfile = optarg; break;
        case 'e': mode_encrypt = 1; break;
        case 'd': mode_encrypt = 1; break;
        case 'h':
        default:
            print_usage(argv[0]);
            return 1;
        }
    }

    if (!key) {
        fprintf(stderr, "Error: key is required\n");
        print_usage(argv[0]);
        return 2;
    }

    FILE *in = stdin;
    FILE *out = stdout;
    if (infile) {
        in = fopen(infile, "rb");
        if (!in) {
            perror("fopen input");
            return 3;
        }
    }
    if (outfile) {
        out = fopen(outfile, "wb");
        if (!out) {
            perror("fopen output");
            if (infile) fclose(in);
            return 4;
        }
    }

    int rc = xor_stream(in, out, (const unsigned char*)key, strlen(key));

    if (infile) fclose(in);
    if (outfile) fclose(out);

    if (rc != 0) {
        fprintf(stderr, "Operation failed (I/O error)\n");
        return 5;
    }
    (void)mode_encrypt; /* 为了清晰保留：XOR 异或是对称的 */
    return 0;
}
