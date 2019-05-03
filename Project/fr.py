import sys
import face_recognition

if (len(sys.argv) != 2):
	print("Missing input image path")
	sys.exit(-1)

# Load the known facial images into numpy arrays
obama_image_1 = face_recognition.load_image_file("1.jpeg")
obama_image_2 = face_recognition.load_image_file("2.jpg")
obama_image_3 = face_recognition.load_image_file("3.jpeg")
unknown_image = face_recognition.load_image_file(sys.argv[1])

obama_face_encoding_1 = face_recognition.face_encodings(obama_image_1)[0]
obama_face_encoding_2 = face_recognition.face_encodings(obama_image_2)[0]
obama_face_encoding_3 = face_recognition.face_encodings(obama_image_3)[0]
unknown_face_encoding = face_recognition.face_encodings(unknown_image)[0]

known_faces = [
    obama_face_encoding_1,
    obama_face_encoding_2,
    obama_face_encoding_3
]

# results is an array of True/False telling if the unknown face matched anyone in the known_faces array
results = face_recognition.compare_faces(known_faces, unknown_face_encoding)

print("Is the input face a picture of Obama? {}".format(all(results)))
