#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>

uint32_t read_and_convert(const char *filename) {
    FILE *file = fopen(filename, "rb");
    uint32_t num;

    if(file == NULL) {
        perror("Error opening file");
        return 0;
    }

    fread(&num, sizeof(uint32_t), 1, file);
    fclose(file);

    // 네트워크 바이트 오더로부터 호스트 바이트 오더로 변환
    num = ntohl(num);

    return num;
}

int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("Usage: add-nbo <file1> <file2>\n");
        return 1;
    }

    uint32_t num1 = read_and_convert(argv[1]);
    uint32_t num2 = read_and_convert(argv[2]);
    uint32_t sum = num1 + num2;

    // 결과를 네트워크 바이트 오더로 변환하여 출력
    sum = htonl(sum);
    int i=0;
    while(sum>0){
        i*=256;
        i+=sum%256;
        sum/=256;
    }
    sum=i;
    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", num1, num1, num2, num2, sum, sum);

    return 0;
}
