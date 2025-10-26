import sqlite3

def dict_factory(cursor, row):
    fields = [column[0] for column in cursor.description]
    return {key: value for key, value in zip(fields, row)}


con = sqlite3.connect("./dbs.sqlite3")
con.row_factory = dict_factory
cur = con.cursor()
tokenlist = []

query = "SELECT * FROM morphs;"
rows = []
for result in cur.execute(query):
    print("parse = {}".format(result["parse"]))
    row = {"id": result["id"], "inflected": result["inflected"], "lesson": result["lesson"], "head": result["head"] }
    parse = result["parse"]
    if "/" in parse:
        tokens = parse.split(" ")
        # print(tokens)
        genders = []
        cases = []
        tokenlist = []
        for token in tokens:    
            if "/" in token:
                #print("got a slash")
                if ("masc" in token) or ("fem" in token) or ("neut" in token):
                    genders = token.split("/")
                else:
                    cases = token.split("/")
            elif ("masc" in token) or ("fem" in token) or ("neut" in token):
                genders.append(token)
            elif ("nom" in token) or ("voc" in token) or ("dat" in token) or ("acc" in token):
                cases.append(token)
            else:
                tokenlist.append(token)
        for gender in genders:
            for case in cases:
                print("case = {}".format(case))
                ab = {"id": result["id"], "inflected": result["inflected"], "lesson": result["lesson"], "head": result["head"] }
                tl = tokenlist.copy()
                tl.append(gender)
                tl.append(case)
                ab['parse'] = " ".join(tl)
                tl.clear()
                rows.append(ab)
    else:
        row['parse'] = parse
        #print(row)
        rows.append(row)
for entry in rows:
    print(entry)
    stmt = "INSERT INTO newmorphs (inflected, head, parse, lesson) VALUES (?, ?, ?, ?);"
    con.execute(stmt, [entry["inflected"], entry["head"], entry["parse"], entry["lesson"]])


con.commit()
con.close()

# CREATE TABLE `morphs` (
#   `id` int(11) NOT NULL,
#   `inflected` varchar(255) DEFAULT NULL,
#   `head` varchar(255) DEFAULT NULL,
#   `parse` varchar(255) DEFAULT NULL,
#   `lesson` int(11) DEFAULT NULL,
#   PRIMARY KEY (`id`)/*,
#   KEY `idx_fulltext` (`inflected`,`head`)*/
# );