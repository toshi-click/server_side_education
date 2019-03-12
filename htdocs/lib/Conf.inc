<?php
/// エラーレベル判定
$setErrorLevel = E_ALL;

/// 表示除外エラーレベルが設定されえているか、論理積を取ってチェック
if (($setErrorLevel & E_NOTICE) == E_NOTICE) {
    $setErrorLevel = $setErrorLevel ^ E_NOTICE;
}
if (($setErrorLevel & E_STRICT) == E_STRICT) {
    $setErrorLevel = $setErrorLevel ^ E_STRICT;
}
if (defined("E_DEPRECATED") && ($setErrorLevel & E_DEPRECATED) == E_DEPRECATED) {
    $setErrorLevel = $setErrorLevel ^ E_DEPRECATED;
}
error_reporting($setErrorLevel);

$bDebug = 1;
/// 接続リソース
define("DB_DSN", "host=postgres port=5432 dbname=training_db user=postgres password=");

/// SQL表示ClientIP
$bDebug = 1;
$tADMIN_REMOTE_IP[] = "127.0.0.1";
// 発行されたSQLを画面に出さない場合は下記をコメントアウト
$tADMIN_REMOTE_IP[] = "192.168.254.1";
