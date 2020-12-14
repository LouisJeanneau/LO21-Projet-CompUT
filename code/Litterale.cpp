#include"code/Litterale.h"
#include <QString>


Litterale* distinguerConstruire(QString s)
{
    int flag1=s.startsWith("[");//programme
    int flag2=s.startsWith("""");//expression
    int flag3=s.contains(".");//reel
    int flag4=s.contains("/");//rationnel
    int l=s.length();
    if(s[0]<='9'&&s[0]>='0')//numerique
    {
        if(flag3==1)//reel
        {
            return new Reel(s.toDouble());
            // return re;
        }
        else if(flag4==1)//rationnel
        {
            QString n1=s.section("/",0,0);
            QString d1=s.section("/",1,1);
            int n=n1.toInt();
            int d=d1.toInt();
            return new Rationnel(&n,&d);

        }
        else //entier
        {
            return new Entier(s.toInt());

        }
    }

    else if(s[0]>='A'&&s[0]<='Z')//Atome
    {
        return new Atome(s);

    }
    else if (flag1==1) //programme
    {
        return new Programme(s.mid(1,l-2));

    }
    else if(flag2==1)//expression
    {
        Atome ae=Atome(s.mid(1,l-2));
        return new Expression(&ae);

    }
    return nullptr;
}


QString Entier::versString() const {
    return QString::number(entier);
}

QString Reel::versString() const {
    return QString::number(reel);
}

QString Rationnel::versString() const {
    return QString::number(numerateur)+"/"+QString::number(denominateur);
}
QString Programme::versString() const {
    return "["+programme+"]";
}
QString Expression::versString() const {
    return """+this->atome->versString()+""";
}
QString Atome::versString() const {
    return atome;
}
void Rationnel::simplifier(int*n,int *d) {
    //if (denominateur == 1) // ou après  simplification ça devient un entier ：interpreteur doit le vérifier d＇ abord
    if(*n==1)return;//pas besion de simplifier
    for(int i=2;i<=*n&&i<=*d;i++)
    {
        if((*n)%i==0&&(*d)%i==0)
        {
            *n=(*n)/i;
            *d=(*d)/i;
            simplifier(n,d);
        }
    }
    this->if_simple=1;
}
