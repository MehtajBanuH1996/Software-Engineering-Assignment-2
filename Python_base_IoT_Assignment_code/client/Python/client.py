import urllib.request
import xml.etree.ElementTree as ET
import matplotlib.pyplot as plt

response = urllib.request.urlopen("http://localhost:8080/")
data = response.read().decode()

root = ET.fromstring(data.strip("\n"))

temperatureList = []
timeList = []
for reading in root.findall('reading'):
    time = reading.find('time').text
    timeList.append(time[time.find(' '):])
    temperatureList.append(int(reading.find('temperature').text))

plt.style.use('ggplot')
plt.title("Temperature Vs Time")
plt.xlabel("Time")
plt.ylabel("Temperature")
plt.grid(True)
plt.plot(timeList, temperatureList, 'blue')
plt.show()

