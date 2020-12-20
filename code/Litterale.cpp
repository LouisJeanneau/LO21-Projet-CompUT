#include"Litterale.h"
#include <QString>
#include "Pile.h"

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

Item ConstructeurLitterale::distinguerConstruire(QString s) {
    int flag1=s.startsWith("[");//programme
    int flag2=s.startsWith("""");//expression
    int flag3=s.contains(".");//reel
    int flag4=s.contains("/");//rationnel
    int l=s.length();
    if(s[0]<='9'&&s[0]>='0')//numerique
    {
        if(flag3==1)//reel
        {
            Litterale* temp = new Reel(s.toDouble());
            return Item(temp, "Reel");
            // return re;
        }
        else if(flag4==1)//rationnel
        {
            QString n1=s.section("/",0,0);
            QString d1=s.section("/",1,1);
            int n=n1.toInt();
            int d=d1.toInt();
            Litterale* temp = new Rationnel(&n,&d);
            return Item(temp, "Rationnel");

        }
        else //entier
        {
            Litterale* temp = new Entier(s.toInt());
            return Item(temp, "Entier");

        }
    }

    else if(s[0]>='A'&&s[0]<='Z')//Atome
    {
        Litterale* temp = new Atome(s);
        return Item(temp, "Entier");

    }
    else if (flag1==1) //programme
    {
        Litterale* temp = new Programme(s.mid(1,l-2));
        return Item(temp, "Programme");
    }
    else if(flag2==1)//expression
    {
        Atome ae=Atome(s.mid(1,l-2));
        Litterale* temp = new Expression(&ae);
        return Item(temp, "Atome");
    }
    return Item(nullptr, "Vide");
}
