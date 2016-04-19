
class Polynomial
{
    vector<double> a;

    double findRoot(double, double);

public:
    Polynomial();

    double getA(int i) const
    {
        return this->a.at(i);
    }
    void setA(int i, double k)
    {
        if (this->a.size()<i+1)
            this->a.resize(i+1)
        this->a.at(i)=k;
    }

    int deg() const;

    Polynomial& operator+=(const Polynomial &q)
    {
        if (this->a.size()>q.a.size())
        {
            for(int i=0;i<q.a.size());i++) this->a.at(i)=this->a.at(i)+q.a.at(i);
            return * this;
        }
        else
        {
            for(int i=0;i<this->a.size());i++)
            {
                vector<double> pom;
                pom=q.a;
                q.a=this->a;
                this->a=pom;
                this->a.at(i)=this->a.at(i)+q.a.at(i);
                return * this;
            }
        }
    }
    const Polynomial operator+(const Polynomial &q) const
    {
        Polynomial ret;
        if (this->a.size()>q.a.size())
        {
            for(int i=0;i<q.a.size());i++) ret.a.at(i)=this->a.at(i)+q.a.at(i);
            return ret;
        }
        else
        {
            for(int i=0;i<this->a.size());i++)
            {
                vector<double> pom;
                pom=q.a;
                q.a=this->a;
                this->a=pom;
                ret.a.at(i)=this->a.at(i)+q.a.at(i);
                return ret;
            }
        }
    };

    Polynomial& operator*=(const Polynomial &q)
    {
        if (this->a.size()>q.a.size())
            for(int i=q.a.size();i<this->a.size());i++) q.a.at(i)=0;
        else
            for(int i=q.a.size();i<this->a.size());i++) this->a.at(i)=0;
        vector pom<double>
        int n=q.a.size();
        for(k=0;k<2*n-1;k++)
            for (int i=0; i<k; i++)
                pom[k]+=q.a.at(i)*this->a[k-i];
        this->a=pom;
        return * this;
    }



    }
    const Polynomial operator*(const Polynomial &q) const
    {
        if (this->a.size()>q.a.size())
            for(int i=q.a.size();i<this->a.size());i++) q.a.at(i)=0;
        else
            for(int i=q.a.size();i<this->a.size());i++) this->a.at(i)=0;
        vector pom<double>
        int n=q.a.size();
        for(k=0;k<2*n-1;k++)
            for (int i=0; i<k; i++)
                pom[k]+=q.a.at(i)*this->a[k-i];
        return pom;
    }

    Polynomial& operator-=(const Polynomial &q)
    {
        if (this->a.size()>q.a.size())
        {
            for(int i=0;i<q.a.size());i++) this->a.at(i)=this->a.at(i)-q.a.at(i);
            return * this;
        }
        else
        {
            for(int i=0;i<this->a.size());i++)
            {
                vector<double> pom;
                pom=q.a;
                q.a=this->a;
                this->a=pom;
                this->a.at(i)=this->a.at(i)-q.a.at(i);
                return * this;
            }
        }
    };
    const Polynomial operator-(const Polynomial &q) const
    {
        Polynomial ret;
        if (this->a.size()>q.a.size())
        {
            for(int i=0;i<q.a.size());i++) ret.a.at(i)=this->a.at(i)-q.a.at(i);
            return ret;
        }
        else
        {
            for(int i=0;i<this->a.size());i++)
            {
                vector<double> pom;
                pom=q.a;
                q.a=this->a;
                this->a=pom;
                ret.a.at(i)=this->a.at(i)-q.a.at(i);
                return ret;
            }
        }
    }

    bool operator==(const Polynomial &q)
    {
        if (this->a.size()==q.a.size())
        {
            for(int i=0;i<q.a.size());i++)
                if (this->a.at(i)!=q.a.at(i)) return false;
            return true;
        }
        else
            return false;
    }

    bool operator!=(const Polynomial &q) const;
    {
        if (this->a.size()==q.a.size())
        {
            for(int i=0;i<q.a.size());i++)
                if (this->a.at(i)!=q.a.at(i)) return true;
            return false;
        }
        else
            return true;
    }
    double v(double x) const;

    friend ostream& operator<<(ostream&, const Polynomial&)
        {
            for (int i = 0; i<this->a.size(); i++)
                cout<<this->getA(i)<<" ";
            cout<<endl;
        }

    const Polynomial differential() const;

    vector<double> rationalRoots() const;
    vector<double> realRoots() const;
};

void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R);
const Polynomial gcd(const Polynomial &, const Polynomial &);
