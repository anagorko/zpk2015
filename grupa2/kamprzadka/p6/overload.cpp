
class Polynomial
{
    vector<double> a;

    double findRoot(double, double);

public:
    Polynomial();

    double getA(int) const;
    void setA(int, double);

    int deg() const;

    Polynomial& operator+=(const Polynomial &q)
    {
        if (this->a.size()>q.a.size())
        {
            for(int i=0;i<q.a.size());i++) this->a[i]=this->a[i]+q.a[i];
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
                this->a[i]=this->a[i]+q.a[i];
                return * this;
            }
        }
    }
    const Polynomial operator+(const Polynomial &q)
    {
        Polynomial ret;
        if (this->a.size()>q.a.size())
        {
            for(int i=0;i<q.a.size());i++) ret.a[i]=this->a[i]+q.a[i];
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
                ret.a[i]=this->a[i]+q.a[i];
                return ret;
            }
        }
    };

    Polynomial& operator*=(const Polynomial &q)
    {
        if (this->a.size()>q.a.size())
            for(int i=q.a.size();i<this->a.size());i++) q.a[i]=0;
        else
            for(int i=q.a.size();i<this->a.size());i++) this->a[i]=0;
        vector pom<double>
        int n=q.a.size();
        for(k=0;k<2*n-1;k++)
            for (int i=0; i<k; i++)
                pom[k]+=q.a[i]*this->a[k-i];
        this->a=pom;
        return * this;
    }



    }
    const Polynomial operator*(const Polynomial &q)
    {
        if (this->a.size()>q.a.size())
            for(int i=q.a.size();i<this->a.size());i++) q.a[i]=0;
        else
            for(int i=q.a.size();i<this->a.size());i++) this->a[i]=0;
        vector pom<double>
        int n=q.a.size();
        for(k=0;k<2*n-1;k++)
            for (int i=0; i<k; i++)
                pom[k]+=q.a[i]*this->a[k-i];
        return pom;
    }

    Polynomial& operator-=(const Polynomial &q)
    {
        if (this->a.size()>q.a.size())
        {
            for(int i=0;i<q.a.size());i++) this->a[i]=this->a[i]-q.a[i];
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
                this->a[i]=this->a[i]-q.a[i];
                return * this;
            }
        }
    };
    const Polynomial operator-(const Polynomial &q)
    {
        Polynomial ret;
        if (this->a.size()>q.a.size())
        {
            for(int i=0;i<q.a.size());i++) ret.a[i]=this->a[i]-q.a[i];
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
                ret.a[i]=this->a[i]-q.a[i];
                return ret;
            }
        }
    }

    bool operator==(const Polynomial &q)
    {
        if (this->a.size()==q.a.size())
        {
            for(int i=0;i<q.a.size());i++)
                if (this->a[i]!=q.a[i]) return false;
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
                if (this->a[i]!=q.a[i]) return true;
            return false;
        }
        else
            return true;
    }
    double v(double x) const;

    friend ostream& operator<<(ostream&, const Polynomial&);

    const Polynomial differential() const;

    vector<double> rationalRoots() const;
    vector<double> realRoots() const;
};

void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R);
const Polynomial gcd(const Polynomial &, const Polynomial &);
