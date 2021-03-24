#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 200

int main(int argc, char **argv)
{
    if (argc < 6)
    {
        printf("�������󣬲����б�outputpath targetsize automode [position path ...]\n");
        printf("���ӣ�����������Чλ�Զ���䣬�����1.img\nbootimg-patch.exe ./1.img 1474560 1 0 ./boot.com 4096 ./process.com");
        getchar();
        return 0;
    }
    char *outputpath = argv[1];

    int targetsize = atoi(argv[2]), automode = atoi(argv[3]);

    printf(automode ? "�Զ����ÿ�����������512�ֽ�ǰ���0x55 0xAA\n" : "�Զ������ѹر�\n");

    // fill 11
    FILE *output = fopen(outputpath, "wb");
    if (output == NULL)
    {
        printf("open %s error!\n", outputpath);
        getchar();
        return 1;
    }
    char fill = 17;
    for (int i = 0; i < targetsize; i++)
    {
        fwrite(&fill, 1, 1, output);
    }
    fclose(output);
    printf("���������̳ɹ�(��С%d)\n", targetsize);

    // insert custom file
    for (int i = 4; i < argc; i += 2)
    {
        int position = atoi(argv[i]);
        char *inputpath = argv[i + 1];
        FILE *input = fopen(inputpath, "rb");
        FILE *output = fopen(outputpath, "rb+");
        if (output == NULL)
        {
            printf("open %s error!\n", outputpath);
            getchar();
            return 1;
        }
        if (-1 == (fseek(output, position, SEEK_SET)))
        {
            printf("seek error\n");
            getchar();
            return 1;
        }

        char buf[BUFLEN + 1];
        int bufcnt;
        while ((bufcnt = fread(buf, 1, BUFLEN, input)) == BUFLEN)
        {
            fwrite(buf, BUFLEN, 1, output);
        }
        fwrite(buf, bufcnt, 1, output);

        fclose(input);
        fclose(output);
    }

    // д����Ч��־
    if (automode)
    {
        if (targetsize < 512)
        {
            printf("�����СС��512���޷�д��\n");
            return 1;
        }
        FILE *output = fopen(outputpath, "rb+");
        if (output == NULL)
        {
            printf("open %s error!\n", outputpath);
            getchar();
            return 1;
        }
        if (-1 == (fseek(output, 510, SEEK_SET)))
        {
            printf("seek error\n");
            return 1;
        }
        char temp[3];
        temp[0] = 85;
        temp[1] = 170;
        temp[2] = 0;
        fwrite(temp, 2, 1, output);
        fclose(output);
        printf("д����Ч��־�ɹ�\n");
    }
    printf("�����������\n");
    getchar();
    return 0;
}