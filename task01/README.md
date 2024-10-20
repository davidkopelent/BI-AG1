# Pokoj č.217
Nepříliš úspěšný akademik Jeník Kopeček se po dalším vyčerpávajícím semestr rozhodl, že si potřebuje trochu odpočinout. Vyžádal si proto u svého nadřízeného roční sabatikl. Ten s tím beze všeho souhlasil. Jednak bylo na Jeníkovi vidět, že vyhoření je ta nejhřejivější věc, která ho v několika posledních měsících potkala, ale také to vedoucímu umožní snížit jeho mzdu na zákonné minimum a bude si tak moci z ušetřených peněz koupit nový telefon, konečně podporující genmoji.

Vzhledem ke snížení mzdy se tedy Jeník během svého tvůrčího volna nemohl věnovat pouze svému výzkumu ionizačních chemomorfních galvanizátorů, ale musel se poohlédnout i po nějaké brigádě. Naštěstí se mu naskytla naprosto neodolatelná nabídka: místo správce v luxusním, ale odlehlém horském hotelu Krakovec, který je přes zimu zcela odříznutý od světa. Pro Jeníka to byla vítaná příležitost najít klid na práci.

V prvních chvílích vše vypadalo idilicky. Luxusní rezort v malebném horském údolí. V okolí nic kromě stromového bludiště. Jeník s rodinou dostali k dispozici nádherný apartmán s výhledem na okolní štíty. V hotelové kuchyni bylo dostatek zásob na celou zimu, ať už jakkoliv mrazivou. Jeníkův syn Daník mohl na své tříkolce brázdit chodby hotelu prakticky do nekonečna.

Přesto se zdálo, jako by s místem něco nebylo v pořádku. Jeník byl na své nejbližší stále více neurvalý a nemohl se vůbec soustředit na svou práci. Celé dny proseděl v hale, nemohl spát ani jíst. Jediné, na co se zmohl, bylo stále dokola házet balónek proti zdi a opět ho chytat. S výzkumem nepohl ani o píď.

Malý Daník nejdříve radostně objevoval různá zákoutí hotelu, postupně ale začal zjišťovat, že zejména s některými místy není něco v pořádku. Připadalo mu, že z některých pokojů se ozývá křík, z jiných pláč, a z některých děsivý smích. Nejhorší pocity měl Daník z pokoje číslo 217. Vždy, když se proháněl okolo, cítil, jak ho něco z pokoje volá: „Píp, píp, Daníku.“

Jednou večer, myslím, že to byla středa, Daníkovi jeho maminka vyrobila z papíru loďku a on se vydal se svým korábem brázdit místní rozlehlé chodby. Zrovna když ve druhém patře během hrůzostrašné mořské bouře odrážel skupinu pirátů, zakopl a loďka zapadla do pootevřených dveří pokoje číslo 217. Ve škvírce dveří nebylo vidět nic jiného, než dvě žluté oči. „Je to jen zvíře,“ utěšoval se Daník. „Chceš svojí loďku, Daníku?“, ozvalo se ovšem šeptem z pokoje. Venku náhle udeřil hrom ihned následovaný bleskem, který ozářil vnitřek pokoje. Daník, strachy bez sebe, se ovšem nedokázal odtrhnout. Před očima měl jen obraz klauna v jedné ruce držícího několik balónků a v druhé ruce jeho loďku. „Chceš svojí loďku, Daníku?“, ozvalo se z pokoje znovu, tentokrát zřetelněji. „Ovšem, že chci. Tatínek mi ale zakázal bavit se s cizími lidmi,“ odvětil Daník. „Ovšem, že zakázal. Moudrý muž je to. Dovol mi se tedy představit. Mé jméno je Robert Šedý, také známý jako Tancující klaun. A ty jsi Daník. Vidíš, teď už se známe a nejsem pro tebe tedy cizí.“ Daník po zralé úvaze odvětil: „Těší mě. Mohu tedy dostat svou loďku?“ A začal natahovat svou ruku do otevřených dvěří. Už měl loďku skoro na dosah, když tu náhle se klaunův obličej v tu nejhrůzostrašnější věc, kterou kdy Daník viděl. Okamžitě stáhl ruku a pokusil se zabouchnout dveře. Klaun, nebo alespoň to co původně klaunem bylo, však strčil do mezery svou nohu a začal se jednou rukou sápat po Daníkovi. Ten se dal okamžitě na útěk, klaun mu byl ale stále v patách, místo balonků náhle třímaje sekyru.

Daník v panice a s kříkem nakonec vyběhl z hotelu a vydal se do přilehlého stromového bludiště. Doufal zřejmě, že se mu podaří se zde před klaunem schovat. Po chvíli bezmyšlenkovitého úprku skrz bludiště najednou Daník zjistil, že kroky za ním zpomalily, ale zároveň že vůbec netuší, kde je. Zpomalil proto a nyní se snaží najít cestu z bludiště ven. Pomůžete mu?

## Rozhraní programu
Vaším úkolem je implementovat šablonu funkce Path find_escape_route(const Map& map, const Beast& beast) (typ Beast je šablonový parametr), která v zadané mapě nalezne nejkratší procházku vedoucí do cíle, na které hrdina (Daník) nebude sežrán nestvůrou (a to ani při vkročení do cíle). Typ Path je seznam pozic, jak jimi bude hrdina postupně procházet (tj. začíná map.hero a končí map.exit), případně prázdný seznam, pokud hrdina nemůže uniknout. Struktura map obsahuje:

hero: počáteční poloha hrdiny,
beast: počáteční poloha nestvůry,
exit: poloha východu,
Tile operator[] (Position p): operátor [], který vrací typ políčka na dané pozici; pro jednoduchost vrací Tile::WALL pro pozice mimo mapu; enum Tile má hodnoty WALL (zeď), EMPTY (volné políčko) a TRAP (past, hrdina na něj nesmí vstoupit stejně jako na zeď).
Struktura Beast implementuje logiku pohybu nestvůry. Je kopírovatelná a implementuje metodu Position move(const Map& map, Position new_hero, Position old_beast) const, která ukazuje reakci nestvůry na pohyb hrdiny. Výsledek této metody závisí pouze na parametrech a vnitřním stavu, který se voláním nemění (tedy pro jeden objekt a stejné parametry bude tato metoda vracet stejný výsledek). Na druhou stranu, nestvůra může (potenciálně) procházet zdmi, překonávat jedním krokem velké vzdálenosti atd. Jediné, co o ní víte je, že nikdy nevystoupí z mapy.

## Bodové podmínky
Můžete získat 1, 5, 7, 10 či 10.1 (bonus) bodů závislosti na efektivitě řešení. Časové limity na jednotlivé testy jsou 15, 5, 8, 7 a 8 sekund.

## Poznámky
Návrh řešení může výrazně usnadnit vyřešení vhodného miniprogtestu.


