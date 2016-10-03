import sys

jake = 0
tyler = 0
sam = 0
brenton = 0

paid = '-1'
print('Please enter Jake\'s bills')
sys.stdout.flush()
while(True):
    paid = raw_input()
    if (paid == ''):
        break
    print('your input was: ', paid)
    jake += float(paid)

paid = '-1'
print('Please enter Tyler\'s bills')
sys.stdout.flush()
while(True):
    paid = raw_input()
    if (paid == ''):
        break
    print('your input was: ', paid)
    tyler += float(paid)

paid = '-1'
print('Please enter Sam\'s bills')
sys.stdout.flush()
while(True):
    paid = raw_input()
    if (paid == ''):
        break
    print('your input was: ', paid)
    sam += float(paid)

paid = '-1'
print('Please enter Brenton\'s bills')
sys.stdout.flush()
while(True):
    paid = raw_input()
    if (paid == ''):
        break
    print('your input was: ', paid)
    brenton += float(paid)

print('Jake: ', jake)
print('tyler: ', tyler)
print('sam: ', sam)
print('brenton: ', brenton)
sys.stdout.flush()

total = jake + tyler + sam + brenton

print('total bills: ', total)
sys.stdout.flush()

average = total / 4

print('average: ', average)
sys.stdout.flush()

jakeDiff = jake - average
tylerDiff = tyler - average
samDiff = sam - average
brentonDiff = brenton - average

avgList = [('Jake', jakeDiff), ('Tyler', tylerDiff), ('Sam', samDiff), ('Brenton', brentonDiff)]

print('avgList: ', avgList)
sys.stdout.flush()

avgList = sorted(avgList, key=lambda tup: tup[1])

print('avgList after sort', avgList)
print('lowest of avgList', avgList[0][1])
print('lowest key of avgList', avgList[0][0])
sys.stdout.flush()

#if the lowest person owes everyone money
if ((avgList[0][1] < 0) and (avgList[1][1] > 0)):
    print(avgList[0][0], ' owes ', avgList[1][0], ' ', round(avgList[1][1], 2), ' dollars.')
    print(avgList[0][0], ' owes ', avgList[2][0], ' ', round(avgList[2][1], 2), ' dollars.')
    print(avgList[0][0], ' owes ', avgList[3][0], ' ', round(avgList[3][1], 2), ' dollars.')

#if the lowest people owe the highest person money
elif ((avgList[2][1] < 0)):
    print(avgList[0][0], ' owes ', avgList[3][0], ' ', round(-avgList[0][1], 2), ' dollars.')
    print(avgList[1][0], ' owes ', avgList[3][0], ' ', round(-avgList[1][1], 2), ' dollars.')
    print(avgList[2][0], ' owes ', avgList[3][0], ' ', round(-avgList[2][1], 2), ' dollars.')

#if the lowest person needs to pay two people
elif (avgList[0][1] + avgList[3][1] < 0):
    print(avgList[0][0], ' owes ', avgList[3][0], ' ', round(avgList[3][1], 2), ' dollars.')
    print(avgList[0][0], ' owes ', avgList[2][0], ' ', round(-(avgList[0][1] + avgList[3][1]), 2), ' dollars.')
    print(avgList[1][0], ' owes ', avgList[2][0], ' ', round(avgList[2][1] + (avgList[0][1] + avgList[3][1]), 2), ' dollars.')

#if the second lowest person needs to pay 2 people
else:
    print(avgList[0][0], ' owes ', avgList[3][0], ' ', round(-avgList[0][1], 2), ' dollars.')
    print(avgList[1][0], ' owes ', avgList[3][0], ' ', round(avgList[0][1] + avgList[3][1], 2), ' dollars.')
    print(avgList[1][0], ' owes ', avgList[2][0], ' ', round(avgList[2][1], 2), ' dollars.')