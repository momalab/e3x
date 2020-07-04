

template <class T>
void Meuclid<T>::checkRec(
    const Rec & v0, const Rec & v,
    const Rec & vb, T et, T ft)
{
//	std::cout << "Meuclid::checkRec 0\n";
    T x = add( mul(v0.a, v.e) , mul(v0.b, v.f) );
    T y = add( mul(vb.a, et) , mul(vb.b, ft) );
//	std::cout << "Meuclid::checkRec 1\n";
    if ( x != y )
        throw "Error: [pej+qfj!=aet+bft] " + x.str() + ":" + y.str();
  	

//	std::cout << "Meuclid::checkRec 2\n";
}


template <class T>
void Meuclid<T>::fillAB(T x, T y)
{
//	std::cout << "Meuclid::fillAB 0\n";
    if (x < y) x.swap(y);
    v.clear();
    Rec r;
    r.a = x;
    r.b = y;
    v.push_back(r);
//	std::cout << "Meuclid::fillAB 1\n";
    int i = 0;
    if ( v[i].b != 0 )
        while ( 1 )
        {
            //v[i].c = v[i].a%v[i].b;
            //v[i].d = v[i].a/v[i].b;
            T::divABRQ(v[i].a, v[i].b, &v[i].c, &v[i].d);
            if ( v[i].c == 0 ) break;
            v.push_back(Rec()); i++;

            v[i].a = v[i - 1].b;
            v[i].b = v[i - 1].c;
        }
//	std::cout << "Meuclid::fillAB 2\n";
}

template <class T>
void Meuclid<T>::fillEF()
{
//	std::cout << "Meuclid::fillEF 0\n";
    int n = v.size() - 1;
//	std::cout << "Meuclid::fillEF 1\n";
    for ( int i = n; i >= 0; i-- )
    {
        v[i].e = et;
        v[i].f = ft;
        for ( int j = i - 1; j >= 0; j-- )
        {
            v[j].e = v[j + 1].f;
            v[j].f = sub( v[j + 1].e, mul( v[j].d, v[j].e ) );
        }

        v[i].e = v[0].e;
        v[i].f = v[0].f;
    }
//	std::cout << "Meuclid::fillEF 2\n";
}

template <class T>
string Meuclid<T>::str() const
{
//	std::cout << "Meuclid::str 0\n";
    string r;
//	std::cout << "Meuclid::str 1\n";
    for ( int i = 0; i < (int)v.size(); i++ )
    {
        r += v[i].a.str() + ' ' + v[i].b.str() + ' ' + v[i].c.str()
             + ' ' + v[i].d.str() + ' ' + v[i].e.str() + ' '
             + v[i].f.str() + ' ' + v[i].g.str() + '\n';
    }
//	std::cout << "Meuclid::str 2\n";
    return r;
}

template <class T>
void Meuclid<T>::fillG()
{
//	std::cout << "Meuclid::fillG 0\n";
    int n = v.size() - 1;
//	std::cout << "Meuclid::fillG 1\n";
    for ( int i = n; i >= 0; i-- )
    {
        checkRec(v[0], v[i], v[i], et, ft);

        v[i].g = add( add( mul(v[i].a, et), mul(v[i].b, ft) ), mul(v[i].e, v[i].f) );

        if (0)if ( v[i].g < 0 )
            {
                T y = add( v[i].e, v[0].b );
                if ( y > 0 )
                {
                    //T x = (-v[i].g)/y + 1;
                    T x = add( divq( (neg(v[i].g)), y) , 1 );
                    //v[i].f += x;
                    v[i].f.addMod(x, mod);
                    v[i].g = add( add( mul(v[0].a, v[i].e),
                                       mul(v[0].b, v[i].f) ), mul(v[i].e, v[i].f) );
                }
            }

        if ( v[i].g > 0 )
        {
            if ( gsmall == 0  || gsmall > v[i].g ) gsmall = v[i].g;
        }
    }
//	std::cout << "Meuclid::fillG 2\n";
}


