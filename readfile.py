import os
import re
ptn = re.compile('.*.json')
src = 'data'
files = os.listdir(src)

json_files = []
for file in files:
    if re.match(ptn, file):
        json_files.append(f'{src}/{file}')

json_files.sort(key=lambda fp: os.path.getctime(fp), reverse=True)
newest_json = json_files[0]
print(newest_json)
