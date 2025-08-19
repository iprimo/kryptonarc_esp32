Uni test 
<!-- https://github.com/platformio/platformio-examples/tree/develop/unit-testing/calculator -->

# Test project
> platformio test

# Test specific environment (check platformIO.ini)
> platformio test -e test_desktop
> platformio test -e esp32dev
> platformio test -e uno

# Process test on native desktop machine (check platformIO.ini)
> platformio test -e native

_+_+_
Windows OS - install PlatfromIO Cli for UniTest
pip install platformio
platformio --version

_+_+_ Generate Certificate

https://www.youtube.com/watch?v=LHUbQtUeQ0o&ab_channel=BrightMindedLtd
https://www.youtube.com/watch?v=LHUbQtUeQ0o&ab_channel=BrightMindedLtd

Summary:
- create a Certificate Signing Request (CSR) with the command:
#(original) openssl req -new -newkey rsa:2048 -nodes -keyout localhost.key -out localhost.csr
 openssl req -new -newkey rsa:2048 -nodes -keyout hw_direct.dev.kryptonarc.com.key -out hw_direct.dev.kryptonarc.com.csr

- self-sign the Certificate with the command:
 #(original) openssl x509 -req -days 365 -in localhost.csr -signkey localhost.key -out localhost.crt
 openssl x509 -req -days 365 -in hw_direct.dev.kryptonarc.com.csr -signkey hw_direct.dev.kryptonarc.com.key -out hw_direct.dev.kryptonarc.com.crt


 - Getting Finger print of a certificate
 	# https://www.jvt.me/posts/2019/04/03/openssl-fingerprint-x509-pem/
 	
 	# (original) openssl x509 -in cert.crt -noout -fingerprint
 	openssl x509 -in hw_direct.dev.kryptonarc.com.crt -noout -fingerprint
	
	# (original) openssl x509 -in cert.crt -noout -fingerprint -sha256
	openssl x509 -in hw_direct.dev.kryptonarc.com.crt -noout -fingerprint -sha256


_+_+_
Get website certificate:

openssl s_client -connect hw_direct.dev.kryptonarc.com:443 -showcerts 2>/dev/null </dev/null | awk '/^.'"hw_direct.dev.kryptonarc.com"'/,/-----END CERTIFICATE-----/{next;}/-----BEGIN/,/-----END CERTIFICATE-----/{print}'


// https://www.lab4iot.com/2021/02/21/esp32-secure-firmware-update-over-the-air-ota/
openssl s_client -connect hw_direct.dev.kryptonarc.com:443 -showcerts 2>/dev/null </dev/null | awk '/^.*'"hw_direct.dev.kryptonarc.com"'/,/-----END CERTIFICATE-----/{next;}/-----BEGIN/,/-----END CERTIFICATE-----/{print}' | sed -e 's/\(.*\)/\"\1\\n\" /g'

openssl s_client -connect hw_direct.dev.kryptonarc.com:443 -showcerts 2>/dev/null </dev/null | awk '/^.*'"hw_direct.dev.kryptonarc.com"'/,/-----END CERTIFICATE-----/{next;}/-----BEGIN/,/-----END CERTIFICATE-----/{print}' | sed -e 's/\(.*\)/\"\1\\n\" /g'

_+_+_ Get Site Finger print
// https://stackoverflow.com/questions/5164804/get-certificate-fingerprint-of-https-server-from-command-line

# SHA1 Fingerprint (orignial command)
openssl s_client -connect <host>:<port> < /dev/null 2>/dev/null | openssl x509 -fingerprint -noout -in /dev/stdin
# SHA1 Fingerprint (Modified)
openssl s_client -connect hw_direct.dev.kryptonarc.com:443 < /dev/null 2>/dev/null | openssl x509 -fingerprint -noout -in /dev/stdin

# SHA256 Fingerprint (orignial command)
openssl s_client -connect hw_direct.dev.kryptonarc.com:443 < /dev/null 2>/dev/null | openssl x509 -fingerprint -sha256 -noout -in /dev/stdin
# SHA256 Fingerprint (Modified)
openssl s_client -connect hw_direct.dev.kryptonarc.com:443 < /dev/null 2>/dev/null | openssl x509 -fingerprint -sha256 -noout -in /dev/stdin


_+_+_



Run the following command in "" path, to run embedded (on Micro) and native (on PC) test cases.
For embedded tests, Micro has to accept the upload of the code.

pio test 
pio test 
pio test 


_+_+_

Light and Sound notifications:

0x46282 : Beep Once - Solid Amber light
0x77299 : Beep Twice - Blue light
0x42729 : Beep 5 times - Flashing Amber light
0x48277 : Sound Alarm - Falshing Red light
0x57991 : Fault Alarm - Soild Red light



