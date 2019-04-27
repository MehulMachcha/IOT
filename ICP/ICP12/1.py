import json
import urllib2
class MyClass(GeneratedClass):
	def __init__(self):
		GeneratedClass_init__(self) 

	def onLoad(self):
		pass

	def onUnload(self):
		pass

	def onInput_onStart(self):
		#self.onStopped() #activate the output of the box
		result = json.loads(urllib2.urlopen(urllib2.Request("https://api.openweathermap.org/data/2.5/weather?q=kansas,us&mode=json&units=metrics&appid=907a0d541e90e08a4700053800659309")).read())
		output_str = "Temperature is " + str(result["main"]["temp"]) + " and pressure is " + str(result["main"]["pressure"])
		tts = ALProxy("ALTextToSpeech")
		tts.say(str(output_str)) 
	
	def onInput_onStop(self):
		self.onUnload()
		self.onStopped()