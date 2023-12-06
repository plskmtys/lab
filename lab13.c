#include <stdio.h>
#include <stdlib.h>


typedef enum LyAllapot {
    alap, l_volt, ll_volt
} LyAllapot;

// futtatás: $	./build/lab in.txt out.txt

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("helytelen argumentumok.\n");
        return 1;
    }

    LyAllapot all = alap;
    int c;
    char buf[4];

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    if (in == NULL || out == NULL) {
        printf("Hiba a fájlok megnyitásakor.\n");
        return 1;
    }

    while ((c = fgetc(in)) != EOF) {
        switch (all) {
            case alap:
                if (c == 'l') {
                    buf[0] = 'l';
                    all = l_volt;
                } else if (c == 'L') {
                    buf[0] = 'L';
                    all = l_volt;
				}else {
                    fprintf(out, "%c", c);
                }
                break;

            case l_volt:
                switch (c) {
                    case 'l':
                        buf[1] = 'l';
                        all = ll_volt;
                        break;
                    case 'y':
                        fprintf(out, "j");
                        all = alap;
                        break;
                    default:
                        fprintf(out, "%c%c", buf[0], c);
                        all = alap;
                        break;
                }
                break;

            case ll_volt:
                switch (c) {
                    case 'l':
                        buf[2] = 'l';
                        buf[3] = '\0';
                        fprintf(out, "%s", buf);
                        all = alap;
                        break;
                    case 'y':
                        fprintf(out, "jj");
                        all = alap;
                        break;
                    default:
                        buf[2] = c;
                        buf[3] = '\0';
                        fprintf(out, "%s", buf);
                        all = alap;
                        break;
                }
                break;
        }
    }

    fclose(in);
    fclose(out);
    printf("done.\n");
    return 0;
}