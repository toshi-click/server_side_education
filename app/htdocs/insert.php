<html>
<head>
</head>
<body>
<?php
require_once "lib/Db.inc";

$db = new Db();
$sql = "
    INSERT INTO training (
         trainingName
        ,trainingAge
    ) VALUES (
    '$_POST[name]'
        ,'$_POST[age]'
    )
    ;
";
$res = $db->query($sql);
?>
追加しました。<BR>
<a href="./index.php">戻る</a>
</body>
</html>
