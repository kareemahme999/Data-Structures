   BTree<char, 5> t;
    char c[] = {'G','I','B','J','C','A','K','E','D','S',
                'T','R','L','F','H','M','N','P','Q'};
    for (char x : c) t.Insert(x);
    t.Print();
