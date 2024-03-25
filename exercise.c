// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #define MAX

// void convert_binary_num()
// {
//     printf("Please input a decimal number:");
//     int num;
//     scanf("%d", &num);
//     char ans[32];
//     int i;
//     for (i = 0; num != 0; num /= 2)
//         ans[i++] = num % 2 + '0';
//     printf("answer is:");
//     for (int j = i - 1; j >= 0; j--)
//         printf("%c", ans[j]);
// }

// void ispar()
// {
//     char s[100];
//     scanf("%s", s);
//     int n = strlen(s);
//     // printf("%d",n);
//     int flag = 0;
//     for (int i = 0, j = n - 1; i <= j; i++, j--)
//     {
//         if (s[i] != s[j])
//         {
//             flag = 1;
//             break;
//         }
//     }
//     if (flag)
//         printf("no");
//     else
//         printf("yes");
// }

// int cmp(const void *a, const void *b)
// {
//     return *(int *)b - *(int *)a;
// }

// void generate()
// {
//     int nums[10];
//     int n = 0;
//     char s[10];
//     scanf("%s", s);
//     for (int i = 0; i < 10; i++)
//     {
//         if (s[i] >= '0' && s[i] <= '9')
//             nums[n++] = s[i] - '0';
//     }
//     qsort(nums, n, sizeof(int), cmp);
//     for (int i = 0; i < n; i++)
//         printf("%d", nums[i]);
// }

// int main()
// {
//     char *s = "1as";
//     // s[1] = 'n';
//     printf("%s",s);
//     return 0;
// }
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int is_palindrome(char *str)
{
    int len = strlen(str);
    int i, j;

    for (i = 0, j = len - 1; i < j; i++, j--)
    {
        if (str[i] != str[j])
        {
            return 0; // 不是回文，返回0
        }
    }

    return 1; // 是回文，返回1
}

int main()
{
    // double a = .2e0;
    // long double b = 5e-3;
    // printf("%d", sizeof(b));


// FILE *file = fopen("C:\\Users\\zhang\\Desktop\\11.txt", "r");
// if (file != NULL) {
//     char line[256];  // 定义一个缓冲区，用来存储每一行的内容
//     while (fgets(line, 256, file) != NULL) {  // 逐行读取文本文件
//         // printf("the Line:");
//         printf("%s", line);  // 输出读取到的内容
//     }
//     fclose(file);  // 关闭文件
// }
}