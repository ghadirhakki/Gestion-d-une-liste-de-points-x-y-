#include <iostream>
using namespace std;

class erreur{
public :
    virtual void affiche(){cout<<"Erreur";}
};

class erreur_vide:public erreur{
public:
    void affiche(){cout<<"\nListe vide !!\n";}

};
class erreur_depassement:public erreur{
public:
    void affiche(){cout<<"\n ERREUR : Depassement de  la taille de la liste !!\n";}

};
class erreur_char:public erreur{
public:
    void affiche(){cout<<"\nERREUR : Veuillez entrer un nombre valide !!\n";}

};

 //________________________________________________________________________________________________________________________________
class maliste;
class point{
    float x,y;
    point * suivant;
public :
    point(float a=0,float b=0,point * s=NULL) {x=a; y=b;suivant=s;}
    friend class maliste;
};
class maliste{
    point * top;
public :
    maliste(point *p=NULL){top=p;}
    void ajouter(){
        point * p = new point;
        cout<<"\nEntrez les coordonees x puis y : \n";
        cin>>p->x>>p->y;
        p->suivant=top;
        top=p;
    };

    void afficher()
    {
        if (top==NULL) { erreur *er ; er=new erreur_vide; throw er; ;}
        else{
            point * ptr1=top;
            int i=1;
            cout<<"\nVotre liste comporte : \n";
            do{
                cout<<"\t Point "<<i<<" : ("<<ptr1->x<<","<<ptr1->y<<")\n";
                ptr1=ptr1->suivant;
                i++;
            }while(ptr1!=NULL);

        }
    };
    void modifier(int position){
        if (top==NULL){erreur *er ; er=new erreur_vide; throw er;}
        else{
            point *ptr=top;
            for(int i=2;i<=position;i++) ptr=ptr->suivant;
            if (ptr==NULL){erreur *er ; er=new erreur_depassement; throw er;}
            cout<<"Entrez les nouvelles coordonees : \n";
            cin>>ptr->x>>ptr->y;
        }
    };
    void supprimer(int position){
        if (top==NULL){erreur *er ; er=new erreur_vide; throw er;}
        else{
            if (position==1) top=top->suivant;
            else {
                point *ptr1=top;
                point *ptr2=NULL;
                for(int i=1;i<=position;i++){
                     if(ptr1->suivant==NULL){
                         if ((i++)!=position){erreur *er ; er=new erreur_depassement; throw er;}
                         ptr2->suivant=NULL; *ptr1=*ptr2; break;
                     }
                    ptr2=ptr1;
                    ptr1=ptr1->suivant;
                }
                *ptr2=*ptr1;
                delete ptr1;
            }
        }
    };
    void visualiser(int position){
        if (top==NULL) {erreur *er ; er=new erreur_vide; throw er;}
        else {
            point *ptr=top;
            for(int i=2;i<=position;i++){
                ptr=ptr->suivant;
                if(ptr==NULL){erreur *er ; er=new erreur_depassement; throw er;}
            }
            cout<<"\t Point "<<position<<" : ("<<ptr->x<<","<<ptr->y<<")\n";
        }
    };
};

//___________________________________________________________________________________________________________________________
int main()
{
    char c;
    int pos,nb;
    maliste l;
    cout<<"\nVotre liste est bien cree mais vide !!\n";

    check :
    cout << "\nSelectionnez une operation : \n \n"<<"\t 1 : Ajouter des points a la liste \n"<<"\t 2 : Modifier un point de la liste\n";
    cout <<"\t 3 : Supprimer un point de la liste\n"<<"\t 4 : Visualiser un point precis de la liste\n";
    cout <<"\t 5 : Afficher la liste entiere \n " <<"\t 6 : Exit \n";
    try{
        cin>>c;
            switch (c)
            {
                case '1' :
                    cout<<"Precisez le nombre de points : ";
                    cin>>nb;
                    for (int i=0;i<nb;i++) l.ajouter();
                    l.afficher();
                    break;
                case '2' :
                    cout<<"Precisez lequel : ";
                    cin>>pos;
                    l.modifier(pos);
                    l.afficher();
                    break;
                case '3' :
                    cout<<"Precisez le point a supprimer : ";
                    cin>>pos;
                    l.supprimer(pos);
                    l.afficher();
                    break;
                case '4' :
                    cout<<"\n Precisez le point a visualiser : ";
                    cin>>pos;
                    l.visualiser(pos);
                    break;
                case '5' :
                    l.afficher();
                    break;
                case '6' :
                    cout<<"\t \t \t \t \a\a Au revoir :)\n \n";
                    return 0;
                default:
                    erreur *er ;er=new erreur_char;throw er;

            }
    }
    catch(erreur *err)     {err->affiche();}
    catch(...)             {cout<<"\nErreur inconnue! \n";}
    goto check;
    return 0;
}
