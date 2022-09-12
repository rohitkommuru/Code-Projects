import cv2

#Obtaining template and video path

video_path = "C:\\Users\\rohit\\OneDrive\\Desktop\\Vid.mp4"
template_path = "C:\\Users\\rohit\\OneDrive\\Desktop\\template.png"


#Scaling the template to an appropriate size and converting to grayscale
template = cv2.imread(template_path, cv2.IMREAD_GRAYSCALE)
scale_percent = 20
width = int(template.shape[1] * scale_percent / 100)
height = int(template.shape[0] * scale_percent / 100)
dim = (width, height)
template = cv2.resize(template, dim, interpolation = cv2.INTER_AREA)


# Matches the template to each frame in the video 
def template_matching():
    capture = cv2.VideoCapture(video_path)
    while (True):
        ret, img = capture.read()
       
        if ret == True:
            gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            res = cv2.matchTemplate(gray, template,cv2.TM_CCOEFF_NORMED)
            min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)
            top_left = max_loc
            bottom_right = (top_left[0] + width, top_left[1] + height)
            cv2.rectangle(img, top_left, bottom_right, 255,2)
            cv2.imshow("Video", img)
            if cv2.waitKey(25) & 0xFF == ord("q"):
                break
        else:
            break
    capture.release()
    cv2.destroyAllWindows()

# Runs the code
if __name__ == "__main__":
    template_matching()
