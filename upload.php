<!DOCTYPE html>
<html>
<body>

<p>php.ini upload_max_filesizes:
<?php
echo ini_get('upload_max_filesize');
?>
</p>

<form action="upload.php" method="post" enctype="multipart/form-data">
    Select file to upload:
    <input type="file" name="fileToUpload" id="fileToUpload">
    <input type="submit" value="Upload" name="submit">
</form>

<?php
$target_file = basename($_FILES["fileToUpload"]["name"]);
// Check if file already exists
if ($target_file != NULL) {
    if (file_exists($target_file)) {
        echo "Sorry, file already exists.";
    } else {
        if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
            echo "The file ". basename( $_FILES["fileToUpload"]["name"]). " has been uploaded.";
        } else {
            echo "Sorry, there was an error uploading your file.";
        }
    }
}
?>

</body>
</html>
