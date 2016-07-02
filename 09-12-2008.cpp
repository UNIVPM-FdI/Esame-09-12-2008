/*
Scrivere un programma per costruire e gestire il registro (lista) degli ordini di un magazzino di pezzi di ricambio.
Il programma può:
1. Inserire un nuovo ordine nel registro in maniera ordinata (crescente) rispetto all'IDcode e nel caso in cui
si abbiano IDcode uguali in base alla data di caricamento dell'ordine.
2. Stampare tutto il contenuto del registro degli ordini.
3. Stampare tutti gli ordini di un cliente mostrando i totali di ogni singolo ordine.
4. Stampare tutti gli ordini successivi ad una data inserita da tastiera.
5. Elimina un ordine dal registro individuandolo attraverso l'IDcode e la sua data di creazione.
Nel registro ci possono esse più ordini dello stesso cliente, quindi IDcode si può ripetere.
*/

#include <iostream>
using namespace std;

struct calendario//stuttura di struttura appartenete a ordine
{
 int anno;
 short int mese;
 short int giorno;
};
struct ordine
{
 int IDcode;
 char prodotto[20];
 int quantita;
 double prezzo;
 calendario data;
 ordine* succ;
};

typedef ordine* registro;

void inserisci_dati(ordine& a);
bool successivo(registro a, ordine b);
void inserisci_ordinatamente(registro& inizio, ordine e);
void stampa(registro inizio);
void stampa_ordini_cliente(registro inizio, ordine e);
void stampa_ordini_data(registro inizio, ordine e);
void elimina_ordine(registro& inizio, ordine e);

int main()
{
    char s;
    registro cliente=0;
    ordine numero;

    do{
        cout << endl << "Ecco quello che puoi fare:";
        cout << endl << "i: Inserisce un nuovo ordine in base all'ID";
        cout << endl << "s: Stampa tutto il registro degli ordini";
        cout << endl << "q: Stampa tutti gli ordini di un cliente mostrando i totali di ogni ordine";
        cout << endl << "t: Stampa tutti gli ordini successivi ad una data inserita da tastiera";
        cout << endl << "e: Elimina un ordine individuato attraverso l'ID e la sua data di creazione";
        cout << endl << "a: Esci dal programma\n";
        cin>>s;
        switch(s){
        case 'i':{
            inserisci_dati(numero);
            inserisci_ordinatamente(cliente,numero);
        break;
        }
        case 's':{
            stampa(cliente);
        break;
        }
        case 'q':{
        cout<<"inserisci l id del cliente"<<endl;
        cin>>numero.IDcode;
        stampa_ordini_cliente(cliente,numero);
        break;
        }
        case 't':{
            cout<<"inserisci la data"<<endl;
            cin>>numero.data.anno>>numero.data.mese>>numero.data.giorno;
            stampa_ordini_data(cliente,numero);
        break;
        }
        case 'e':{
            cout<<"inserisci IDCode dell ordine da eliminare"<<endl;
            cin>>numero.IDcode;
            cout<<"inserisci la data dell ordine "<<endl;
            cin>>numero.data.giorno>>numero.data.mese>>numero.data.anno;
            elimina_ordine(cliente,numero);
        break;
        }
        case 'a':{
        break;
        }
        default:{
            cout<<"lettera non consentita"<<endl;
        break;
        }
        }
    }while(s!='a');

    return 0;
}

void inserisci_dati(ordine& a){
cout<<"inserisci l' IDCODE del prodotto"<<endl;
cin>>a.IDcode;
cout<<"inserisci il nome del prodotto"<<endl;
cin>>a.prodotto;
cout<<"inserisci la quantità di questo prodotto"<<endl;
cin>>a.quantita;
cout<<"inserisci il prezzo dei prodotti"<<endl;
cin>>a.prezzo;
cout<<"inserisci la data di consegna GG MM AA"<<endl;
cin>> a.data.giorno>>a.data.mese>>a.data.anno;
}

void inserisci_ordinatamente(registro& inizio, ordine e){
registro p=0,q,r;
for(q=inizio;q!=0&&q->IDcode<=e.IDcode;q=q->succ){//il for cicla innanzitutto per IDCODE
   if (q->IDcode == e.IDcode) {//e poi controlla con l if se quello esistente nella lista è uguale a quello che si vuole inserire
    if (successivo(q, e))//infine controlla la data per inserirlo per data e poi scorre la lista e lo inserisce ordinatamente
        p=q;
    else {
        p=q;
    }
}
else//se l' id code è diverso fa l inserimento normale senza controllo delle date
    p=q;
}
    r=new ordine;
    *r=e;
    r->succ=q;
    if(q==inizio)inizio=r;
    else p->succ=r;

}

bool successivo(registro a, ordine b){//questa funzione serve per confrontare due date e determinare se sono uguali o una precedente e l altra successiva
if(a->data.anno<b.data.anno)return true;
else if (a->data.mese<b.data.mese)return true;
else if (a->data.giorno<b.data.giorno)return true;
else return false;
}

void stampa(registro inizio){//classica stampa
if(inizio==0)cout<<"lista vuota"<<endl;
while(inizio!=0){
    cout<<"il cliente con IDcode "<<inizio->IDcode<<"che ha con nome prodotto " <<inizio->prodotto<<" in quantità "<<inizio->quantita<<" per un prezzo unitario di "<<inizio->prezzo<<endl;
    cout<<"in data "<<inizio->data.giorno<<" "<<inizio->data.mese<<" "<<inizio->data.anno<<endl;
    inizio=inizio->succ;
}
}

void stampa_ordini_data(registro inizio, ordine e){//stampa tutti gli in base al successivo di quella data inserita
if(inizio==0)cout<<"lista vuota"<<endl;
while(inizio!=0){
    if(successivo(inizio,e)){
        cout<<"il cliente con IDcode "<<inizio->IDcode<<"che ha con nome prodotto " <<inizio->prodotto<<" in quantità "<<inizio->quantita<<" per un prezzo unitario di "<<inizio->prezzo<<endl;
        cout<<"in data "<<inizio->data.giorno<<" "<<inizio->data.mese<<" "<<inizio->data.anno<<endl;
        }
        inizio=inizio->succ;
    }
}

void elimina_ordine(registro& inizio, ordine e){//elimina l ordine dalla lista per IDCode se ne sono due elimina quello con idcode e data corrispondenti
bool flag;
registro p, q;
for (q = inizio; (q!=0 && q->IDcode!=e.IDcode)||(q->data.giorno!=e.data.giorno||q->data.mese!=e.data.mese||q->data.anno!=e.data.anno); q=q->succ)
p = q;
if (q == 0) flag=false;
if (q == inizio) inizio = q->succ;
else p->succ = q->succ;
e = *q;
delete q;
flag=true;
if(flag){//da notare che la funzione è void e non bool come di solito per le estrazioni quindi si è creato un bool flag per stampare a video
    cout<<"l' elemento con IDcode "<<e.IDcode<<" è stato eleiminato"<<endl;
    }
    else{
        cout<<"elemento non presente"<<endl;
    }
}

void stampa_ordini_cliente(registro inizio, ordine e){// stampa per IDcode e fa la somma
double somma=0;
if(inizio==0)cout<<"lista vuota"<<endl;
while(inizio!=0){
if(inizio->IDcode==e.IDcode){
    cout<<"\nil cliente con IDcode "<<inizio->IDcode<<" con il seguente prodotto "<<inizio->prodotto<<" da ritirare in data "<<inizio->data.giorno<<" "<<inizio->data.mese<<" "<<inizio->data.anno;
    cout<<"\nla somma comlessiva è "<< inizio->quantita*inizio->prezzo<<endl;;//somma complessiva di quell ordine
    somma+=inizio->quantita*inizio->prezzo;
}
    inizio=inizio->succ;
}
cout<<"\n\nla somma di tutti gli ordini e' "<<somma<<endl;//questa somma è la somma di tutti gli ordini di quel cliente
}
