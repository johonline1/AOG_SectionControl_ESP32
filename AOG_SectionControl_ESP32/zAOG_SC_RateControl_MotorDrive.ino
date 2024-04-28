void motorDrive(void)
{
	if (Set.RateControlLeftInst == 1) {
	//if (pwmDrive > 0) bitSet(PORTB, 4);  //set the correct direction
	//analogWrite(Set.FlowPWMLeft_PIN, pwmDrive);
	}
	else 
	//manual motor drive
	{
		if (Set.RateControlPWM == 0)
		{	//if rate switch is toggled -> set Output high
			if (RateManUpLeft) { 
				_digitalWrite(Set.FlowDirLeft_PIN, HIGH); _digitalWrite(Set.FlowPWMLeft_PIN, HIGH); 
				if (Set.debugmodeRelay && (Set.RateSWLeft_PIN < 255)) { Serial.println("Rate left manual up"); }
				}
			if (RateManDownLeft) {
				_digitalWrite(Set.FlowDirLeft_PIN, LOW); _digitalWrite(Set.FlowPWMLeft_PIN, HIGH);
				if (Set.debugmodeRelay && (Set.RateSWLeft_PIN < 255)) { Serial.println("Rate left manual down"); }
			}
			if (RateManUpRight) { _digitalWrite(Set.FlowDirRight_PIN, HIGH); _digitalWrite(Set.FlowPWMRight_PIN, HIGH); }
			if (RateManDownRight) { _digitalWrite(Set.FlowDirRight_PIN, LOW); _digitalWrite(Set.FlowPWMRight_PIN, HIGH); }
			//toggle switch not pressed = set all low
			if (!(RateManUpLeft || RateManDownLeft || RateManUpRight || RateManDownRight))
				{ _digitalWrite(Set.FlowDirRight_PIN, LOW); _digitalWrite(Set.FlowPWMRight_PIN, LOW); _digitalWrite(Set.FlowDirLeft_PIN, LOW); _digitalWrite(Set.FlowPWMLeft_PIN, LOW);
				}
			
		}
	}
}
