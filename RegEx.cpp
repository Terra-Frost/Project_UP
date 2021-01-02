#include  <iostream>
#include  <cstdlib>

const string errorSymbols = "^*+?.";
using  namespace  std;
int normalize(string& reg)
{
    int numberOfSpeshalChar=0
    if(reg[reg.size()=='\\')return -1;
    if(reg.find(reg[0],1,4))return -2;
    for(int i=1;i<reg.size()-1;i++)
    {
        if(reg[i]=='^')return -3;

        if(reg[i]=='\\'){
                swap(reg[i],reg[i+1]);
                i++;
        }
          if(reg.find(reg[i],1,4))
        {

            if(++numberOfSpeshalChar>2)return -4;
            if(reg.find(reg[i+1],1,3))return -5;
        }
    }
    return 0;
}
bool isContaint(string str, string reGex,int indexStr)
{
        for(int indexRegex = reGex.size();indexRegex>=0;indexRegex--)
        {
            if(indexStr<0 && indexRegex>0)return 0;
            switch(reGex[indexRegex])
            {
                case '^':
                    if(str[indexStr]==reGex[indexRegex])return 1;
                    else return 0;
                case '.':break;
                case '?':
                    if(str[indexStr]==reGex[--indexRegex])indexStr--;
                    indexRegex--;
                    break;
                case '*':
                    while(str[indexStr]==reGex[--indexRegex] && indexStr>=0)indexStr--;
                    indexRegex--;
                    break;
                case '+':
                    if(str[indexStr]==reGex[--indexRegex])indexStr--;
                     else return 0;
                    while(str[indexStr]==reGex[--indexRegex] && indexStr>=0)indexStr--;
                    indexRegex--;
                    break;
                case '\\':indexRegex--;
                default :
                    if(str[indexStr]==reGex[indexRegex])indexStr--;
                        else return 0;
            }

        }
        return 1;

}
bool findRegex(string str,string reg)
{
    for(int i=str.size();i>=0;i--)
    {
        if(isContaint(str,reg,i))return 1;
    }
    return 0;
}
int main()

{

 string str = "bbbb";
 string reg = "a+";
 //normalize(reg);
 cout<<findRegex(str,reg);

return 0;

}
