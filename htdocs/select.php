<html>
<head>
    <meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
    <meta http-equiv="cache-control" content="no-cache">
    <meta http-equiv="pragma" content="no-cach">
</head>
<body>
<table border="1">
    <tr>
        <td>No</td>
        <td>名前</td>
        <td>年齢</td>
    </tr>
    <?php
    require_once "lib/Db.inc";

    $db = new Db();
    $sql = "
    SELECT
        *
    FROM
        training
    ;
";
    $res = $db->query($sql);
    if ($res->count()) {
        for ($i = 0; $i < $res->count(); $i++) {
            $aData = $res->fetchRow($i);
            echo "<tr>";
            echo "<td>" . $aData['id'] . "</td>";
            echo "<td>{$aData['trainingname']}</td>";
            echo "<td>{$aData['trainingage']}</td>";
            echo "</tr>";
        }
    } else {
        echo "<tr><td colspan=\"3\">データがありません</td></tr>";
    }
    ?>
</table>
<a href="./index.php">もどる</a>
</body>
</html>
