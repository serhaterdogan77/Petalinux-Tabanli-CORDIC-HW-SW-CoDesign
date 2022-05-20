#define TERMINAL "/dev/ttyPS0"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/mman.h>
#include <math.h>
#include <time.h>


int nmbr1[255];
int nmbr2[255];

int main()
{
	unsigned int gpio_size = 0x8000;
	off_t gpio_pbase = 0x41200000;
	long long* gpio64_vptr;
	long long* bram64_vptr;
	int fd2;

	char* portname = TERMINAL;
	int fd;
	int wlen;
	char* xstr = "Lutfen hesaplanmasi gereken degerleri giriniz!!!\n";
	int xlen = strlen(xstr);
	fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0) {
		printf("Error opening %s: %s\n", portname, strerror(errno));
		return -1;
	}
	wlen = write(fd, xstr, xlen);
	if (wlen != xlen) {
		printf("Error from write: %d, %d\n", wlen, errno);
	}

	do {
		unsigned char buf[80];
		int rdlen;

		rdlen = read(fd, buf, sizeof(buf) - 1);
		if (rdlen > 0) {

			buf[rdlen] = 0;
			printf("%s \n", buf);

			int flag = 0;
			int i == 0;
			while (i < strlen(buf)) {
				if (buf[i] == ' ') {
					flag = 1;
				}
				else {
					if (flag == 0) {
						nmbr1[i] = buf[i] - '0';

					}
					else {
						nmbr2[i] = buf[i] - '0';


					}
				}
				i++;
			}
			int value1 = nmbr1[1] + nmbr1[0] * 10;
			int value2 = nmbr2[4] + nmbr2[3] * 10;


			if ((fd2 = open("/dev/mem", O_RDWR | O_SYNC)) != -1) {
				gpio64_vptr = (long long*)mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, gpio_pbase);
				*(gpio64_vptr) = value1;
				*(gpio64_vptr + 1) = value2;


				int pres = *(gpio64_vptr + 1);
				printf("%d \n:", pres);

				char res[20];
				sprintf(res, "%d", pres);
				int reslen = strlen(res);
				write(fd, res, reslen);

				close(fd2);
			}

		}
		else if (rdlen < 0) {
			printf("Error from read: %d: %s\n", rdlen, strerror(errno));
		}
		else { /* rdlen == 0 */
			printf("Timeout from read\n");
		}

	} while (1);
}