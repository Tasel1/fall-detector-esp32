# Alert Payloads: SMS and Voice TTS

## SMS Alert Format
The system sends an SMS to all personal contacts in the prioritized list when a fall is detected and not canceled within the 60-second window.

### Template
`[Fall Detection Watch] FALL DETECTED! Emergency alert for [USER_NAME]. Location: [GOOGLE_MAPS_LINK or "Coordinates unavailable"]. Help is on the way!`

### Example SMS
`[Fall Detection Watch] FALL DETECTED! Emergency alert for User123. Location: https://www.google.com/maps?q=55.7558,37.6173. Help is on the way!`

## Voice TTS (Emergency Services)
The system initiates a voice call to emergency services (e.g., 112) and plays a pre-defined message using an external TTS service or local voice sample playback (SIM800L audio path).

### Default Message
"Emergency alert. A fall has been detected for the wearer of this device. Location: [LATITUDE], [LONGITUDE]. I repeat, a fall has been detected. Please send assistance."
