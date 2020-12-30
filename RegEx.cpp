#include  <iostream>
#include  <cstdlib>

using  namespace  std;
void normalize(string& reg)
{
    for(int i=0;i<reg.size();i++)
    {
        if(reg[i]=='\\')swap(reg[i],reg[i+1]);
    }
}
bool isContaint(string str, string reGex)
{

        int indexStr = str.size();
        for(int indexRegex = reGex.size();indexRegex>=0;indexRegex--)
        {
            switch(reGex[indexRegex])
            {
                case '.':break;
                case '?':
                    if(str[indexStr]==reGex[--indexRegex])indexStr--;
                    break;
                case '*':
                    while(str[indexStr]==reGex[--indexRegex])indexStr--;
                    break;
                case '+':
                    if(str[indexStr]==reGex[--indexRegex])indexStr--;
                     else return 0;
                    while(str[indexStr]==reGex[--indexRegex])indexStr--;
                    break;
                case '\\':indexRegex--;
                default :
                    if(str[indexStr]==reGex[indexRegex])indexStr--;
                        else return 0;
            }
        }
        return 1;

}
int main()

{

 string str = "cbba";
 string reg = ".ba?";
 //normalize(reg);
 cout<<isContaint(str,reg);

return 0;

}
