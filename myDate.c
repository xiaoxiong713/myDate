#include <stdio.h>
#include <string.h>
#include <time.h>
/*
    author: xiaoxiong
    website: https://xiaoxiong713.com
    date: 2022,4,19
    version: 1.0
*/

int getstat(int a);
char *print_line(int, int,int start, int max, char *str, int *ji, int hello);
int format(int y, int m, int d);

char *_xx_to_string(int a)
{

    static char res[3] = {};
    memset(res, 0, sizeof(res));
    if (a < 10)
    {
        res[0] = a + 48;
        // res[1] = '\n';
    }
    if (a >= 10)
    {
        res[0] = a / 10 + 48;
        res[1] = a % 10 + 48;
        // res[2] = '\n';
    }
    return res;
}

int to_num(const char *str, int len)
//字符串 转换为 数字， 字符串的长度为<=4
{
    int a = 0;

    if (len <= 4)
    {
        if (len == 1)
        {
            a = str[0] - 48;
            return a;
        }
        if (len == 2)
        {
            a = (str[0] - 48) * 10;
            a += (str[1] - 48);
            return a;
        }
        if (len == 3)
        {
            a = (str[0] - 48) * 100;
            a += (str[1] - 48) * 10;
            a += (str[2] - 48);
            return a;
        }
        if (len == 4)
        {
            a = (str[0] - 48) * 1000;
            a += (str[1] - 48) * 100;
            a += (str[2] - 48) * 10;
            a += (str[3] - 48);
            return a;
        }
    }

    return a;
}

int getruinian(int y)
{
    if((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
    {
        //是闰年
        return 1;
    }
    else
    {
        return 0;
    }

}

int getYearStart(int a)
{
    //这个函数是： 计算任意年份（1980 ， 2018 ， 2000 ）的一月一号是星期几？
    int year = a;
    int aaa = 0;
    if (!getruinian(a))
    {
        aaa = 1;
    }
    int startYearWeek = (3 - (year / 100) % 4) * 2 + aaa; //一年的第一天是星期几？
    int xiangju = year - (year / 100) * 100;

    //每过一年起始星期数加1，如果是闰年就再额外加1，这样就可以得出该世纪中任何一年的相对星期数

    return ((xiangju / 4) + xiangju + startYearWeek) % 7;
}

int getMonthStart(int y, int m)
{
    //计算任意年份的其中的某月的一号是星期几？
    int result;
    int year = getYearStart(y);

    if (m == 1)
    {
        //边界问题，默认计算0代表星期日，但是我想让7代表星期日
        if(year % 7 == 0)
        {
            year = 7;
        }
        return year;
    }
    if (m == 2)
    {
        year += 31;

    }
    else if(m == 3)
    {
        year = year + 31 + 28 + getruinian(y);

    }
    else
    {
        year = year + (30 * (m - 2) + getstat(m)) + 28 + getruinian(y);
    }

    int res = 0;
    if (year % 7 == 0)
    {
        res = 7;
    }
    else
    {
        res = year % 7;
    }
    return res;
}

int getstat(int a)
{
    //最后加几个？
    if (a == 3)
    {
        return 1;
    }

    if (a == 4)
    {
        return 2;
    }

    if (a == 5)
    {
        return 2;
    }

    if (a == 6)
    {
        return 3;
    }

    if (a == 7)
    {
        return 3;
    }

    if (a == 8)
    {
        return 4;
    }
    if (a == 9)
    {
        return 5;
    }
    if (a == 10)
    {
        return 5;
    }
    if (a == 11)
    {
        return 6;
    }
    if (a == 12)
    {
        return 6;
    }

}

int getMaxDays(int y, int a)
{
    //某个月
    int days;
    if (a == 2)
    {
        days = 28;
    }
    else
    {
        days = 30;
    }

    if (a == 1 || a == 3 || a == 5 || a == 7 || a == 8 || a == 10 || a == 12)
    {
        days ++;
    }
    if (getruinian(y) && a == 2)
    {
        days ++;
    }

    return days;

}
char *print_line(int sys_year, int sys_month, int start, int max, char *str, int *ji, int hello)
{

    int h = *ji;
    //最后一行，填充
    if (h == 500)
    {
        for (int i = 0; i < 7; ++i)
        {
            strcat(str, "   ");
        }
        return str;
    }
    //起始的星期，和 最大的天数

    for (int j = 1; j <= 7; ++j)
    {
        if (j >= start || hello )
        {
            h ++;
            if (h < 10)
            {
                strcat(str, " ");
            }
            //彩色vt100
            if (format(sys_year, sys_month, h))
            {
                // printf("\033[41;37m %d \033[0m", i);
                strcat(str, "\033[41;37m");
                strcat(str, _xx_to_string(h));
                strcat(str, "\033[0m ");

            }else{
                strcat(str, _xx_to_string(h));
                strcat(str, " ");
            }
            
        }
        else
        {

            strcat(str, "   ");
        }


        //到了一个月的最大值，停止
        if(h == max)
        {
            h = 500;
            *ji = h;

            //月份的天数完了，就打印x填充空隙

            for (int i = 0; i < (7 - j); ++i)
            {
                strcat(str, "   ");
            }
            return str;
        }
        //满7 换行
        if ((start - 1  + h) % 7 == 0 )
        {
            *ji = h;
            return str;
        }
    }

    *ji = h;
    return str;
}
void ppp3(int year, int a, int b, int c)
{
    char str1[100] = {};
    char str2[100] = {};
    char str3[100] = {};

    //中间记录， 寄存器一样
    int a1 = 0;
    int a2 = 0;
    int a3 = 0;

    for (int i = 0; i < 6; ++i)
    {
        printf("%s\t", print_line(year,a,getMonthStart(year, a), getMaxDays(year, a), str1, &a1, i));
        printf("%s\t", print_line(year,b,getMonthStart(year, b), getMaxDays(year, b), str2, &a2, i));
        printf("%s\t", print_line(year,c,getMonthStart(year, c), getMaxDays(year, c), str3, &a3, i));
        printf("\n");

        memset(str1, 0, sizeof(str1));
        memset(str2, 0, sizeof(str2));
        memset(str3, 0, sizeof(str3));
    }
}
void p_header(int a, int b, int c)
{
    printf("          %d月", a);
    printf("\t\t");

    printf("          %d月", b);
    printf("\t\t");

    printf("          %d月", c);

    printf("\n");


    printf("一 二 三 四 五 六 日");
    printf("\t\t");

    printf("一 二 三 四 五 六 日");
    printf("\t\t");

    printf("一 二 三 四 五 六 日");
    printf("\n");
}//end of p_header

void ppp(int y, int a)
{
    if (a != 0)
    {
        //某个月
        int days;
        printf("一\t二\t三\t四\t五\t六\t日\n");
        days = getMaxDays(y, a);
        for (int i = 0; i < getMonthStart(y, a) - 1; ++i)
        {
            printf("\t");
        }
        for (int i = 1; i <= days; ++i)
        {
            //vt100彩色
            if ( format(y, a, i))
            {
                printf("\033[41;37m%d\033[0m\t", i);

            }
            else
            {
                printf("%d\t", i);
            }

            if ((getMonthStart(y, a) - 1  + i) % 7 == 0 )
            {
                printf("\n");
            }


        }
    }
    else if (a == 0)
    {
        // 打印一年， 三排连着打印
        p_header(1, 2, 3);
        ppp3(y, 1, 2, 3);
        p_header(4, 5, 6);
        ppp3(y, 4, 5, 6);
        p_header(7, 8, 9);
        ppp3(y, 7, 8, 9);
        p_header(10, 11, 12);
        ppp3(y, 10, 11, 12);

    }


}

int format(int y, int m, int d)
{

    time_t time_ptr;
    struct tm *tmp_ptr = NULL;
    int system_year, system_month, system_day;
    // 获取当前时间
    time(&time_ptr);
    tmp_ptr = localtime(&time_ptr);

    system_year = tmp_ptr->tm_year + 1900;
    system_month = tmp_ptr->tm_mon + 1;
    system_day = tmp_ptr->tm_mday;
    if (system_year == y && system_month == m && system_day == d)
    {
        return 1;

    }else {
        return 0;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    int year = 0;
    int month = 0;

    if (argc == 2)
    {
        //打印一整年
        year = to_num(argv[1], strlen(argv[1]));
        ppp(year, month);
    }
    else if(argc > 2)
    {
        //打印某个月
        year = to_num(argv[1], strlen(argv[1]));
        month = to_num(argv[2], strlen(argv[2]));
        ppp(year, month);
    }

    return 0;
}//end of main
