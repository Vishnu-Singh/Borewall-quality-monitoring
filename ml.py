import pandas as pd
from sklearn.neighbors import KNeighborsClassifier
import b_w_ml as data
dataset=pd.read_csv('dataset.csv')
dataset.set_index("ph",drop=False)
x=dataset.loc[0:53,'ph':'turbidity']
y=dataset.loc[0:53,'percentage']

print(x)
print(y)

model=KNeighborsClassifier(n_neighbors=1)
model.fit(x,y)

while True:
    pre=data.cal_data()[0]
    if (len(pre)==2):
        d=[]
        d.append(pre)
        print("Value: ".format(pre))
        print("Water Quality: {}%".format(model.predict(d)[:1]))
    data.upload()
