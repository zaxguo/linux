import os
import sys
import subprocess

keywords =  [('-', 3138411), ('_', 2367468), ('CN', 2173930), ('x', 2167328), ('X', 1467356), ('NA', 1221265), ('ENRON', 1131341), ('OU', 1088779), ('RECIPIENTS', 1084883), ('/O', 1081881), ('Content', 1041166),            ('subject', 868593), ('cc', 769809), ('Enron', 637870), ('date', 613970), ('HOU', 587798), ('bcc', 552388), ('text', 528889), ('ID', 528767), ('Type', 524550), ('plain', 519059), ('Transfer', 518950),           ('Version', 518792), ('encoding', 517846), ('Mime', 517299), ('charset', 517270),
 ('ECT@ECT', 506210), ('ascii', 478986), ('FileName', 430293), ('Folder', 345416), ('e', 341957), ('pm', 326630), ('mail', 319748), ('origin', 313920), ('PDT', 270451), ('PST', 253061), ('J', 245858),            ('message', 242263), ('to', 236660), ('company', 212028), ('power', 206153), ('time', 205155), ('Origin', 203076), ('Message', 201136), ('John', 200374), ('Mark', 193960), ('market', 188831), ('Non', 188147),   ('document', 185503), ('price', 184449), ('folder', 182199), ('am', 178665),
 ('new', 178043), ('notfound1', 172592), ('Cc', 170485), ('year', 166135), ('Corp', 165037), ('information', 164591), ('California', 161391), ('day', 161116), ('Enron@Enron', 153121), ('week', 152514),           ('thank', 152451), ('Jeff', 145314), ('Enron@ENRON', 143859), ('deal', 139220), ('Energy', 138750), ('energy', 138041), ('M', 136037), ('good', 134334), ('David', 132569), ('business', 130089), ('gas',          128967), ('state', 128648), ('question', 123389), ('notfound2', 121787), ('Houston',
 121589), ('Folders\\All', 121092), ('contract', 119796), ('May', 117110), ('Mike', 111189), ('issue', 110883), ('Privileged.pst', 110199), ('re', 109193), ('Tue', 108898), ('meeting', 108126), ('S', 106751),    ('Richard', 105533), ('ECT', 105441), ('Chris', 103698), ('email', 103679), ('D', 101045), ('Scott', 99913), ('today', 99409), ('rate', 98858), ('James', 98454), ('Jones', 97820), ('New', 97818), ('service',    97158), ('Power', 95305)]

for i in range(0, 100):
    command = ['./mail_search', keywords[i][0]]
    outfile = f'keyword100/keyword{i}'
    out = open(outfile, 'w')
    print(' '.join(command), 'redirects to', outfile)
    subprocess.run(command, stdout=out)
    out.close()
