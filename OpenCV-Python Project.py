import cv2
import numpy as np

# Charger l'image en niveaux de gris
image = cv2.imread('C:\\Users\\Arthur\\OneDrive\\Bureau\\Justin Tester\\Justin Tester\\Image_Test.jpg', cv2.IMREAD_GRAYSCALE)

cv2.namedWindow('image', cv2.WINDOW_NORMAL)  # Allow window to be resizable

# Vérifier si l'image a été correctement chargée
if image is None:
    print("Erreur : Impossible de charger l'image.")

else:
    cv2.moveWindow('image', 5, 100)
    cv2.imshow('image', image)
    cv2.resizeWindow('image', 800, 600)  # Resize the window to fit your screen
    cv2.waitKey(100)  # Petite pause

    # Appliquer un flou pour lisser l'image
    blurred_image = cv2.GaussianBlur(image, (9, 9), 0)

    # Fonction de mise à jour du seuil
    def update_threshold(*args):
        # Obtenir les valeurs des trackbars
        min_threshold = cv2.getTrackbarPos('Min Threshold', 'Threshold Adjust')
        max_threshold = cv2.getTrackbarPos('Max Threshold', 'Threshold Adjust')

        # Appliquer le seuillage avec les seuils actuels
        _, thresholded_min = cv2.threshold(blurred_image, min_threshold, 255, cv2.THRESH_BINARY)
        _, thresholded_max = cv2.threshold(blurred_image, max_threshold, 255, cv2.THRESH_BINARY_INV)

        # Combinaison des deux seuillages
        thresholded_image = cv2.bitwise_and(thresholded_min, thresholded_max)

        # Afficher l'image seuilée
        cv2.imshow('Threshold Adjust', thresholded_image)
        cv2.moveWindow('Threshold Adjust', 5, 5)

    # Créer une fenêtre pour les trackbars
    cv2.namedWindow('Threshold Adjust', cv2.WINDOW_NORMAL)  # Allow window to be resizable

    # Initialiser les trackbars
    cv2.createTrackbar('Min Threshold', 'Threshold Adjust', 0, 255, update_threshold)
    cv2.createTrackbar('Max Threshold', 'Threshold Adjust', 0, 255, update_threshold)

    # Initialiser les seuils
    cv2.setTrackbarPos('Min Threshold', 'Threshold Adjust', 120)
    cv2.setTrackbarPos('Max Threshold', 'Threshold Adjust', 145)

    # Afficher l'image seuilée initiale
    update_threshold()

    # Attendre la touche "OK" pour valider les paramètres
    while True:
        update_threshold()  # Mise à jour continue de l'image en fonction des trackbars
        key = cv2.waitKey(1) & 0xFF
        if key == ord('o'):  # Appuyez sur "o" pour valider
            break

    # Après validation, créer l'image finale avec les paramètres choisis
    min_threshold = cv2.getTrackbarPos('Min Threshold', 'Threshold Adjust')
    max_threshold = cv2.getTrackbarPos('Max Threshold', 'Threshold Adjust')

    _, thresholded_min = cv2.threshold(blurred_image, min_threshold, 255, cv2.THRESH_BINARY)
    _, thresholded_max = cv2.threshold(blurred_image, max_threshold, 255, cv2.THRESH_BINARY_INV)
    thresholded_image = cv2.bitwise_and(thresholded_min, thresholded_max)

    # Paramètres pour la détection de blob
    params = cv2.SimpleBlobDetector_Params()
    params.filterByArea = True
    params.minArea = 100
    params.maxArea = 1000
    params.blobColor = 255
    params.filterByCircularity = False
    params.filterByConvexity = False
    params.filterByInertia = False

    # Créer un détecteur de blobs avec les paramètres définis
    detector = cv2.SimpleBlobDetector_create(params)

    # Détecter les blobs sur l'image seuilée
    keypoints = detector.detect(thresholded_image)

    # Afficher le nombre de blobs détectés
    print(f"Nombre de blobs détectés : {len(keypoints)}")

    # Dessiner les blobs détectés sur l'image originale
    image_with_blobs = cv2.drawKeypoints(image, keypoints, np.array([]), (0, 0, 255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

    # Si des blobs sont détectés, alors la pièce est caractérisée comme non conforme
    if len(keypoints) > 0:
        # Position du texte
        position = (image.shape[1] - 200, 30)
        font = cv2.FONT_HERSHEY_SIMPLEX
        font_scale = 0.6
        color = (0, 0, 255)  # Texte en rouge
        thickness = 2

        # Ajouter le texte à l'image
        cv2.putText(image_with_blobs, "Piece Non Conforme", position, font, font_scale, color, thickness)

    # Redimensionner l'image pour qu'elle s'adapte à la fenêtre
    screen_res = 1280, 720  # Change this to your screen resolution
    scale_width = screen_res[0] / image_with_blobs.shape[1]
    scale_height = screen_res[1] / image_with_blobs.shape[0]
    scale = min(scale_width, scale_height)
    window_width = int(image_with_blobs.shape[1] * scale)
    window_height = int(image_with_blobs.shape[0] * scale)
    resized_image = cv2.resize(image_with_blobs, (window_width, window_height))

    # Afficher l'image redimensionnée avec les blobs détectés
    cv2.imshow('Blob', resized_image)
    cv2.resizeWindow('Blob', window_width, window_height)  # Resize the window to fit your screen
    cv2.waitKey(0)
    cv2.destroyAllWindows()