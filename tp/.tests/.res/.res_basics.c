#include <stdio.h>
#include <stdlib.h>
#include ".res_basics.h"
#include "../../alloc.h"

unsigned long r_power_of_two(int n)
{
  if( n == 0)
    return 1;
  //bitewise
  return (unsigned long)2 <<(n-1);
}


unsigned long r_binary_to_int(int bin)
{
  int compt = 0;
  unsigned long res = 0;
  while (bin != 0)
    {
      res += (bin%10)*r_power_of_two(compt);
      bin/=10;
      compt++;
    }
  
  return res;
}

//guess why I did that if you read this
//it's a completely stupid as fuck
//but I'm to lazy
int is_good(int a, int b)
{
  int tmp = a/b;
  return ((tmp*b) == a);
}

void r_decompose(int n, int* tab)
{
  int k = 0;
  int i = 2;
  while (n != 1)
    {
      if (is_good(n,i))
	{
	  tab[k] = i;
	  n/=i;
	  k++;
	}
      
      else
	i++;
    }
}

void swap(int* a, int* b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
} 

void r_reverse_arr(int* arr,size_t length)
{
  for(size_t i = 0; i <length/2; i++){
    swap(&arr[i],&arr[length-i-1]);
  }
}

int modulo(int a, int b)
{
  return a<0 ? b<0 ?a%b-b:a%b+b : a%b;
}


void r_n_shift_arr(int* arr, size_t length, int n)
{
  int* new_arr = r_malloc(length*sizeof(int));
  for (size_t i = 0; i < length; i++)
    new_arr[i] = arr[i];

  for (size_t i = 0; i<length; i++)
    arr[modulo(i+n,length)] = new_arr[i];

  r_free(new_arr);
}



void r_replace(char s1[], char s2[])
{

  int i = 0;
  while (s1[i] != 0 && s2[i] != 0)
    {
      *(s1+i)  = s2[i];
      i++;
    }
}

char rot_char(char s,int dec)
{
  if( 'a' <= s && s <= 'z')
    return (char)'a'+modulo((s-'a')+dec,26);
  
  if('A' <= s && s <= 'Z')
    return (char)'A'+modulo((s-'A')+dec,26);

  return s;
}

void r_cesar(char s[], int dec)
{
  dec = modulo(dec,26);
  int i = 0;
  while (s[i] != 0)
    {
      s[i] = rot_char(s[i],dec);
      i++;
    }
}

char* substring(char* s, int start, int len)
{
  char* sub = r_malloc((len+1)*sizeof(char));
  
  for(int i = 0; i<len; i++)
    sub[i] = s[start+i];

  sub[len] = 0;
  return sub;
}
int get_next_number(char* s,int* i)
{
  int len = 0;
  int start = *i;
  while (s[*i] != 0 && '0'<= s[*i] && s[*i] <= '9')
    {
      len ++;
      *i += 1;
    }

  char* sub = substring(s,start,len);
  int res = atoi(sub);

  r_free(sub);
  return res;
}
    

unsigned long r_basic_calculator(char* s)
{

  unsigned long res = 0;
  int i = 0;
  res += get_next_number(s,&i);
  while (s[i] != 0 && (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'))
    {
      if (s[i] == '+')
	{
	  i++;
	  res += get_next_number(s,&i);
	}
      
    else if (s[i] == '-')
      {
	i++;
	res -= get_next_number(s,&i);
      }

    else if (s[i] == '*')
      {
	i++;
	res *= get_next_number(s,&i);
      }
      
    else if (s[i] == '/')
      {
	i++;
	res /= get_next_number(s,&i);
      }
    }
  
  return res;
}

