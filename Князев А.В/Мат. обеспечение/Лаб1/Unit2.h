//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
template<class TDrawer>
class ArrayMap
{
        struct TId
        {
                char      key[255];
                int       val;
                TId*      next;
        } *fst;
        int n;
        TId** find(char str[255])
        {
                TId** p = &fst;
                while((*p)!=0)
                        if(strcmp((*p)->key,str)==0) break;
                        else p=&((*p)->next);
                if((*p)==0)return 0;
                return p;
        }
        public:
        ArrayMap():n(0),fst(0) {}
        ~ArrayMap()
        {
                TId* p = fst;
                while(p!=0)
                {
                        TId* t=p;
                        p=p->next;
                        delete t;
                }
        }
        void Add(char key[255], int val)
        {
                TId** t = find(key);
                if(t!=0)return;
                TId *p = new TId;
                p->val=val;
                strcpy(p->key,key);
                p->next=fst;
                fst=p;
                n++;
        }
        int Search(char key[255])
        {
                TId** a = find(key);
                if (a==0) return -1;
                return (*a)->val;
        }
        bool Delete(char key[255])
        {
                TId** k = find(key);
                if (k==0) return false;
                TId* p=(*k)->next;
                delete (*k);
                (*k)=p;
                n--;
                return true;
        }
        void draw(TDrawer dr)
        {
                TId* p = fst;
                while(p!=0)
                {
                       dr.draw(p->val,p->key);
                       p=p->next;
                }
        }
};
//---------------------------------------------------------------------------
#endif
