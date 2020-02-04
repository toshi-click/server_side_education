<?php
//----------------------------------------------------------------------
//
// テーブル管理ツール
//
//----------------------------------------------------------------------
require_once("lib/Db.inc");

foreach ($_REQUEST as $key => $value) {
    ${$key} = $value;
}

?>
<html>
<head>
<title></title>
</head>
<body class="text">
<span class="title">Table Mgr</span>
<br>
<form name="frm" action="<? echo($_SERVER['PHP_SELF']) ?>" METHOD="POST">
    <table border="0" cellspacing="5" cellpadding="0" class="head">
        <tr>
            <td align="center">
                sql<br>　<br>↓
            </td>
            <td align="">
                <TEXTAREA name="sSql" ROWS="10" COLS="72" class="sql"></TEXTAREA>
            </td>
        </tr>
        <tr>
            <td colspan="2" align="">
                <input type="submit" name="bnSubmit" value="  g o  ">
            </td>
        </tr>
    </table>
<?
if ($bnSubmit) {
        $sSql = addslashes($sSql);// addslashes — 文字列をスラッシュでクォートする
        $aBuf = explode("\'", $sSql);// explode — 文字列を文字列により分割する
        $sSql = implode("'", $aBuf);// implode — 配列要素を文字列により連結する

        //$sSql = str_replace ("\' ","' ", $sSql);
        //$sSql = str_replace (" \'"," '", $sSql);
        echo("<hr>");
        $server_addr = getenv("SERVER_ADDR");// getenv — 環境変数の値を取得する
        $db = new Db();
        unset($aBuf);// unset — 指定した変数の割当を解除する
        $aBuf = explode(" ", ltrim($sSql));
           $sStateType = $aBuf[0];
              $sStateType = strtoupper($sStateType);// strtoupper — 文字列を大文字にする

    $sSql = preg_replace("(\t)", " ", $sSql);// preg_replace — 正規表現検索および置換を行う
    $sSql = preg_replace("(\r\n|\n)", " ", $sSql);

    if ($sStateType == "SELECT") {
        echo("<b>Read SQL / StatType = $sStateType</b><br>\n");
        // SQL実行
        $result = $db->query($sSql);// 「queryメソッド」- 特にエスケープする必要が無いときや単純に決まったデータを1回だけ取り出したい時
        for ($i = 0; $i < $result->count(); $i++) {
            $aFetch = $result->fetchRow($i);
            $aRow[$i] = $aFetch;
        }

        for ($j = 0; $j < $result->numFields(); $j++) {
            $aColName[$j] = $result->getFieldName($j);
            $aColType[$j] = $result->getFieldType($j);
            $aColSize[$j] = $result->getFieldSize($j);
        }

        $nRows = count($aRow);
        $nCols = count($aColName);

        $result->free();
        $db->disc();
    } else {
//$sSql=mbstring_convert($sSql,"SJIS","EUC");
        echo("<b>Write SQL / StatType = $sStateType</b><br>");

        // SQL実行
//echo($sSql);
        $sSql = preg_replace("\t|\r\n|\n", "", $sSql);
//$sSql = str_replace ("'","\'", $sSql);
//$sSql = str_replace ("\' ","' ", $sSql);
//$sSql = str_replace (" \'"," '", $sSql);
//        $sSql = str_replace ("\\'", "'", $Sql);
        $result = $db->query($sSql, "off");
        if (!$result) {
            echo("An error occured to Exec query($sSql)\n");
        } else {
            echo("sql = $sSql<br>");
        }
        exit;
    }

?>
//            sql = <? echo($sSql) ?><br>
        rows = <? echo($nRows) ?><br>
        cols = <? echo($nCols) ?><br>
        <table border="1" cellspacing="1" cellpadding="0" class="text">
            <tr>
<?        for ($j=0; $j<count($aColName); $j++) {    ?>
                <td align="" width="30" class="head">
                    <? echo($aColName[$j]) ?><br>
                    <? echo($aColType[$j]) ?><br>
                    [<? echo($aColSize[$j]) ?>]
                </td>
<?        }    ?>
            </tr>
<?//        for ($i=0; $i<$nRows && $i<2000; $i++) {    ?>
<?        for ($i=0; $i<$nRows; $i++) {    ?>
            <tr>
<?
for ($j=0; $j<$nCols; $j++) {
    if ($aRow[$i][$j] == "") {
        $sVal = "　";
    } else {
        $sVal = $aRow[$i][$j];
    }
?>
                <td align="" width="30">
                    <? echo("$sVal") ?>
                </td>
<?            }    ?>
            </tr>
<?        }    ?>
        </table>
<?    }    ?>

    </form>
</body>
</html>
