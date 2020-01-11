# E-Store-Project
To do:
Nir:
- Menue changes
- System changes without polymorphism

Ben:
- Finish operators of Buyer, Seller. - DONE
- Finish User


Questions for Keren:
1. Check why when sending User(s) in c'tor, there's an error marked by the compiler in Buyer_Seller.cpp.

2. When implementing an assignment operator in a class that has nested class - Do we need to call the assignment operator of the nested class or only call the copy c'tor in the init line?  line 22 in User.cpp .

3. When we put the copy c'tor in private we can't use him in system. (it looks like we wanna use him from the outside but don't wanna let the user do the same)

4. About dinamic_cast, should it be diffrent tmp for buyer and buyerseller?