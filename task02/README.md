# Jeden den v životě Antonína Dlaníka

Kdesi daleko v zaostalých a nezmapovaných končinách onoho cípu Západního spirálního ramene naší Galaxie, který si rozhodně nemůže dělat nároky na módnost, leží jedno malé, bezvýznamné žluté slunce. Kolem něj zhruba ve vzdálenosti sto padesáti miliónů kilometrů obíhá naprosto zanedbatelná nepatrná modrozelená planeta, na níž formy života vzešlé z opic jsou tak úžasně primitivní, že se dosud domnívají, že digitální hodinky jsou docela šikovný nápad. V samém srdci kontinentu zvaném Evropa se pak nachází jedna titěrná zemička, jejímž ministerským předsedou je Antonín Dlaník. Antonín Dlaník bydlel v domě umístěném v mírném svahu na samém konci vesnice, kam se před třemi lety přestěhoval, protože na bydlení v hlavním městě již neměl nervy.

Ve čtvrtek v osm ráno vzbudil Antonína pocit, že se země otřásá. Mátožně se probudil, vstal a bloumal po pokoji. Když otevřel okno, uviděl buldozer. Hned uhodl, kolik uhodil. Našel pantofle a vyrazil z ložnice ven do mrazivého jitra. O patnáct vteřin později už byl venku a ležel před obrovským žlutým buldozerem, který se valil zahradní pěšinou.

Okamžitě k němu přispěchal pan L. Prosser, zaměstnanec obecní rady. „Nechte toho, pane Dlaník,“ říkal, „tohle přece nemůžete vyhrát. Nemůžete ležet před buldozerem donekonečna. Měl jste právo vznést námitky nebo předložit protinávrhy v patřičné lhůtě.“ „V patřičné lhůtě?“ opičil se Antonín. „V patřičné lhůtě? Dozvěděl jsem se o tom včera!“ „Ale pane Dente, ty plány byly přístupné na místním plánovacím úřadě tři čtvrtě roku.“ „To jo, a jakmile jsem se to dozvěděl, hned jsem se taky na ně šel podívat. Zrovna jste se nenamáhali na ně upozorňovat, co? Musel jsem je nakonec jít hledat do sklepa. S baterkou. Abych nakonec oznámení našel na dně zamčené registračky, kterou vecpali na zrušený záchod a na dveře dali ceduli Pozor, leopard!.“ „Pane Dlaník, rád bych vám poskytl jednu věcnou informaci. Dovedete si představit, jakou škodu by asi utrpěl tenhle buldozer, kdybych ho prostě pustil a převálcoval vás?“ „Jakou?“ zeptal se Antonín. „Vůbec žádnou,“ odvětil Prosser a nervózně odmašíroval.

To Antonína dopálilo. Takhle přeci nemůže nikdo mluvit s ministerským předsedou! A navíc, již před několika lety pověřil svého ministra digitalizací celého systému pro Dohled nad Silničními Řešeními (DSŘ), aby již nikdo nemusel absolvovat ty ponižující cesty do sklepení úřadů. Nasupeně se zvedl a oddupal si to zpět do svého stále ještě stojícího domu. Ze skříně vytáhl svůj oblíbený tesilový oblek, nasedl do své ministerské limuzíny a nepřístojnou rychlostí se vypravil do své kanceláře. Do sídla vlády se dostal v rekordním čase a ještě předtím, než si stihl poslat pro svou první kávu, nasupeně vpadl do kanceláře ministra zodpovědného za digitalizaci. Jinak distinguovaný premiér se na ministra rozkřikl a po přibližně dvou minutách bylo hotov. Ministr už není ministr. Nepomohlo mu ani to, že systém je téměř hotový, ani to, že státu ušetřil velkou hromadu peněz. Když už se jednou Antonín rozhodl, nic ho nedokázalo zviklat.

„Tak, to by bylo.“ pomyslel si Antonín, když konečně s kávou usedl ve své kanceláři. „Teď už jen najít někoho, kdo dotáhne tu digitalizaci.“ Ve stejnou chvíli do místnosti pokorně vešel jeden z Antonínových blízkých spolupracovníků, kterému nikdo neřekl jinak než Žížala. „Tebe mi snad seslalo samo nebe!“ prohlásil Antonín, když si nově příchozího všiml. „Od teď máš na starost digitalizaci DSŘ, do konce týdne chci analýzu.“

Žížala je zkušený šíbr, proto se ihned chopil příležitosti. A začal plánovat. Původní systém se musí pochopitelně zahodit. Na výrobu nového by mohl od ministerského předsedy dostat alespoň dva roky. A hlavně, zakázku musejí dostat ti správní lidé. V neposlední řadě by bylo krásné do systému přidat funkcionalitu, která mu umožní si k bídnému platu sem tam trochu přilepšit. „No jistě!“ zvolal nahlas, což ho samotného překvapilo. Jedním z největších problémů současného řízení je že podané žádosti o stavbu jsou zpracovávány sekvenčně a zodpovědné úřady jsou navíc pověstné svou nerychlostí. Co takhle fronta žádostí, ve které lze za nějaké všimné trochu předbíhat?

Rozhraní programu
Vaším úkolem je implementovat šablonu třídy Queue (šablonový parametr je typ ukládaných prvků), která má metody:

bool empty() const: Otestuje, zda je fronta prázdná.

size_t size() const: Vrátí počet prvků ve frontě.

Ref push_last(T x): Vloží prvek x na konec fronty a vrátí odkaz na tento prvek ve frontě typu Ref. Vrácený odkaz musí zůstat validní až do vyjmutí prvku z fronty nebo zrušení celé fronty.

T pop_first(): Vyjme první prvek z fronty.

size_t position(Ref ref) const: Vrátí pozici prvku určeného odkazem ref ve frontě (počítáno od začátku fronty od nuly).

void jump_ahead(Ref ref, size_t jmp): Posune prvek určený odkazem ref o jmp pozic vpřed ve frontě. Odkaz ref musí zůstat validní i po provedení této operace. Pokud je jmp větší než pozice prvku, bude prvek posunut na začátek fronty (pozici 0).

Datový typ Ref musí být definován uvnitř šablony Queue. Představuje odkaz na prvek, který je platný po celou dobu přítomnosti prvku ve frontě bez ohledu na jeho pohyb. Musí být kopírovatelný, ale nemusí obsahovat žádné veřejné metody či atributy.

Bodové podmínky
Můžete získat 1, 3, 7 nebo 10 bodů dle efektivity vašeho řešení. Časové limity na jednotlivé testy jsou 15, 1, 1.6 a 4 sekundy.

Poznámky
Opět doporučujeme vyřešit příslušné miniprogtesty.