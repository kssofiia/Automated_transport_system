import cv2
import numpy
import serial

if __name__ == '__main__':
    def callback(*arg):
        print (arg)

print("connect...")
ser = serial.Serial('COM11', 9600)
print("good")
cap = cv2.VideoCapture (1, cv2.CAP_DSHOW)
prev = 0

while True:
    flag, img = cap.read()
    img1 = img[70:160, 180:270]
    img2 = img[160:250, 180:270]
    img3 = img[250:340, 180:270]

    img = cv2.rectangle(img, (180, 70), (270, 160), (0, 255, 255), 1)
    img = cv2.rectangle(img, (180, 160), (270, 250), (0, 255, 255), 1)
    img = cv2.rectangle(img, (180, 250), (270, 340), (0, 255, 255), 1)
    detector = cv2.QRCodeDetector()
    data1, bbox1, clear_qrcode = detector.detectAndDecode(img1)
    data2, bbox2, clear_qrcode = detector.detectAndDecode(img2)
    data3, bbox3, clear_qrcode = detector.detectAndDecode(img3)
    check = 0
    if data1:
        #print("3", data1)
        cv2.circle(img1, (int(bbox1[0][0][0]), int(bbox1[0][0][1])), 5, (0,255,0), -1)    
        cv2.circle(img1, (int(bbox1[0][1][0]), int(bbox1[0][1][1])), 5, (0,255,0), -1)   
        ser.write(str(3).encode('utf-8'))
        #ser.write(str(data1).encode('utf-8'))
        #print(str(3).encode('utf-8'))
        check = 3
    if data2:
        print("2", data2)
        cv2.circle(img2, (int(bbox2[0][0][0]), int(bbox2[0][0][1])), 5, (0,255,0), -1)    
        cv2.circle(img2, (int(bbox2[0][1][0]), int(bbox2[0][1][1])), 5, (0,255,0), -1)    
        ser.write(str(2).encode('utf-8'))
        #ser.write(str(data2).encode('utf-8'))
        check = 2
    if data3:
        print("1", data3)
        cv2.circle(img3, (int(bbox3[0][0][0]), int(bbox3[0][0][1])), 5, (0,255,0), -1)    
        cv2.circle(img3, (int(bbox3[0][1][0]), int(bbox3[0][1][1])), 5, (0,255,0), -1)   
        ser.write(str(1).encode('utf-8'))
        #ser.write(str(data3).encode('utf-8'))
        check = 1
    cv2.imshow("img", img)
    cv2.imshow("img1", img1)
    cv2.imshow("img2", img2)
    cv2.imshow("img3", img3)
    ch = cv2.waitKey(5)
    if ch == 27:
        break

cap.release()
cv2.destroyAllWindows()
