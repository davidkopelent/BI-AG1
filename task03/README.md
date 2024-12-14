# Na většího

Nejdříve si zopakujme, jak vlastně obr vypadal. Můžeme klidně říci, že obr byl na první pohled člověk, ale obrovský, náramný a celkem co do velikosti téměř přehnaný. Obři měli nosy všelijaké, vousiska rozmanitá, hlavy rozcuchané, nebo ulízané, či plešaté. Tedy vzezření venkoncem lidské až na to, že vlas obří byl tlustý jako dietní párek, palec u nohy větší než kančí kýta a právě tahle nadměrnost z nich činila stvoření nelidská.

Neboť co jest lidského na člověku? Právě to, že není ani příliš velký, ani příliš malý. A takoví obyčejní človíčkové bydlívali v údolích okolo Vltavy, zatímco na vysokých temenech pražských hor sídlili obři. Človíčkové v údolích se plahočili za denním chlebem a obři je líně pozorovali z výšky hřebenů hor. Celkem nic nedělali a většinou se nudili.

Jednou časně zrána se nad Prahou narodil nápadně krásný den. Takový, jakých nebývá v roce mnoho. Kdy sluníčko hřeje od časného rána až do západu, hřeje, ale nepálí, kdy ze Strahova je vidět až na Šumavu a snad ještě dál, zkrátka a dobře voňavý, průzračný a vlahý všední den. Lidi se radovali v údolích a obři si lebedili na horách.

Toho dne při západu slunce stáli obři vztyčeni na nejvyšších hřebenech a chytali na svá obrovitá záda poslední vlažné paprsky sluníčka, které se už chystalo za obzor. A jak tak stojí zády ke slunci, všimli si, že se jim stíny prodlužují. Čím bylo sluníčko níže, tím dále se plazily obří stíny. “Kluci,” povídá obr na Čihadle, “pojďte si zahrát na většího!” Jak prej se hraje na většího? hulákali druzí obři přes údolí a stráně. Čihadelský obr prohlásil, že jednoduše: komu stín dopadne dál do kraje, ten je větší než ten, jehož stín dopadne blíže do kraje.

Od té doby, vždycky když končil jasný den, bylo možno vidět obry na horách, jak vystupují na špičky, aby protáhli svůj stín, jak hulákají z kopce na kopec škádlíce se jako kluci, prostě jak si hrají na většího. Dneska je těžko říci, který z nich to byl, jenž začal první fixlovat, neboli hrát falešně. Dal si pod nohy dva velikánské placáky a při západu na ně vystoupil. To se ví, že jeho stín se doplazil nejdál, až do Turčianského sv. Martina, vždyť stál na nejvyšším bodě ze všech obrů, to je každému dneska jasné.

Tehdy však to obři nemohli hned tak prokouknout. O fyzice neměli tuchy. Ale žil tam v údolí jakýsi intelektuál, prý bývalý docent, a ten vysvětlil podstatu fixlování jednomu pasáčkovi krav. Ten pasáček to zase řekl z hlouposti třem obrům. A stalo se, že při každé hře na většího vznikala různá překvapení: neboť fixlovali všichni. Až jednou se jednomu obru podařilo vrhnout stín daleko za Dnipro a řekl s klidem, že už hrát nebude, že je největší.

Rozhraní programu
Vaším úkolem je implementovat funkci std::vector<Block> highest_tower(const std::vector<Block>& available_blocks), která určí, jak ze zadaných bloků available_blocks postavit co nejvyšší věž:

Struktura Block obsahuje atributy x a y (šířku a délku) a h (výšku bloku), které jsou nezáporná celá čísla.
Při stavbě není možné bloky nijak otáčet a každý blok může být použit nejvýše jednou (ale může být zadáno k dispozici bloků stejných rozměrů).
Blok nesmí přesahovat blok pod ním (tj. pokud máme blok b a na něm postavený blok u, tak musí platit b.x >= u.x a b.y >= u.y).
Návratovou hodnotou je seznam bloků, jak mají být postaveny na sebe odspodu vzhůru.
Bodové podmínky
Můžete získat 3, 6, 10 nebo 12 bodů dle efektivity vašeho řešení. Časové limity jsou 15, 1, 3.5 a 4 sekundy. Test rychlosti II dává částečné body řešením rychlejším než 8 sekund.