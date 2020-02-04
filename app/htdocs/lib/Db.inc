<?php
// アロー演算子 と呼ばれます。インスタンスのプロパティを参照する演算子
// $a->$name は、プロパティの名前に対して $name に代入されている値を指定する
// 「以下の2つは等価」
// ーーーーーーーーーーーー
// echo $a->name;
// ーーーーーーーーーーーー
// $property = 'name';
// echo $a->$property;
//-------------------------------------------------------
//
// DB クラス
//
//-------------------------------------------------------
require_once("Conf.inc");

unset($gConn);
unset($gResult);

class Db
{
    var $conn = "";        // 接続リソース
    var $result = "";    // 結果リソース

    //---------------------------------------------------
    // コンストラクタ
    // DB接続
    //---------------------------------------------------
    public function __construct()
    {
        global $tADMIN_REMOTE_IP;
        global $gConn;
        global $gResult;

        $this->conn = $gConn;
        $this->result = $gResult;

        @$this->conn = pg_connect(DB_DSN);// pg_connect(<接続文字列>) ->PostgreSQLへ接続する。

//        if (pg_connection_status($this->conn) != PGSQL_CONNECTION_OK) {    /// 接続リソース無し
//            @$this->conn = pg_connect(DB_DSN);// pg_connect(<接続文字列>) ->PostgreSQLへ接続する。
//            $errmsg = $php_errormsg;
//            /// connect後の接続リソース判定
//            $conn_result = @pg_connection_status($this->conn);
//            if ($conn_result != PGSQL_CONNECTION_OK) {
//                // エラー内容
//                $msg = "CONNECT: connect error.\n";
//                $msg .= "REASON: $errmsg\n";
//
//                // File::putLog($msg);
//                if (!in_array($_SERVER['REMOTE_ADDR'], $tADMIN_REMOTE_IP)) {
//                    // Mail::send(EMERGENCY_ADMIN_MAIL, PGSQL_CONN_ERROR, "DB CONN ERROR", $msg);
//                    print("ただいまデータベースのメンテナンス中です。<br>");
//                    print("申し訳ありませんが、しばらくしてから再度アクセスをお願い申し上げます。<br>");
//                    exit;
//                } else {
//                    die("$errmsg<br>\n");
//                }
//            } else {
//                // print("<div class=\"text\"><font color=\"blue\" size=\"2\">PGSQL_CONNECTION:$conn_result</font></div><br>\n");
//            }
//        }
        $gConn = $this->conn;
        $gResult = $this->result;
    }

    //---------------------------------------------------
    // DB切断
    //---------------------------------------------------
    public function disc()
    {
        @pg_close($this->conn);
    }

    //---------------------------------------------------
    // query実行
    //---------------------------------------------------
    // 「public」アクセス権を表現するためのキーワード
    // [public function query()]->メソッドの宣言
    public function query($sql)// ($sql)引数の値をプロパティに保存する
    {
        global $tADMIN_REMOTE_IP;
        global $gConn;
        global $gResult;
        $sql = preg_replace("(\t)", " ", $sql);
        $sql = preg_replace("(\r\n|\n)", " ", $sql);
        // 'SERVER_ADDR' -> 現在のスクリプトが実行されているサーバーの IP アドレス。
        if (in_array($_SERVER['REMOTE_ADDR'], $tADMIN_REMOTE_IP)) {
            print("<div class=\"text\"><font color=\"blue\" size=\"2\">$sql</font></div><br>\n");
        }
        @$this->result = pg_query($this->conn, "$sql");// pg_query(<SQL文>, <リンクID>)->SQL文の発行。
        $errmsg = $php_errormsg;
        if (!$this->result) {
            $this->disc();

            // エラー内容
            $msg = "REQUEST_METHOD: $_SERVER[REQUEST_METHOD]\n";
            $msg .= "REQUEST_URI: $_SERVER[REQUEST_URI]\n";
            $msg .= "HTTP_USER_AGENT: $_SERVER[HTTP_USER_AGENT]\n";
            $msg .= "REMOTE_IP: $_SERVER[REMOTE_ADDR]\n";
            $msg .= "SQL: $sql\n";
            $msg .= "REASON: $errmsg\n";

            // File::putLog($msg);
            // 'SERVER_ADDR' -> 現在のスクリプトが実行されているサーバーの IP アドレス。
            if (!in_array($_SERVER['REMOTE_ADDR'], $tADMIN_REMOTE_IP)) {
                // Mail::send(EMERGENCY_ADMIN_MAIL, PGSQL_EXEC_ERROR, "DB EXEC ERROR", $msg);
                print("ただいまデータベースのメンテナンス中です。<br>");
                print("申し訳ありませんが、しばらくしてから再度アクセスをお願い申し上げます。<br>");
                exit;
            } else {
                die("<div class=\"text\">$msg</div><br>\n");
            }
        }

        $gConn = $this->conn;
        $gResult = $this->result;

        return (new Db());
    }

    public function create_test($sql, $count, $max_count)
    {
        global $tADMIN_REMOTE_IP;
        global $gConn;
        global $gResult;

        $sql = preg_replace("(\t)", " ", $sql);
        $sql = preg_replace("(\r\n|\n)", " ", $sql);
        if (in_array($_SERVER['REMOTE_ADDR'], $tADMIN_REMOTE_IP)) {
            print("<div class=\"text\"><font color=\"blue\" size=\"2\">$sql</font></div><br>\n");
        }
        @$this->result = pg_query($this->conn, "$sql");
        $errmsg = $php_errormsg;
        if (!$this->result) {
            $this->disc();

            // エラー内容
            $msg = "REQUEST_METHOD: $_SERVER[REQUEST_METHOD]\n";
            $msg .= "REQUEST_URI: $_SERVER[REQUEST_URI]\n";
            $msg .= "HTTP_USER_AGENT: $_SERVER[HTTP_USER_AGENT]\n";
            $msg .= "REMOTE_IP: $_SERVER[REMOTE_ADDR]\n";
            $msg .= "SQL: $sql\n";
            $msg .= "REASON: $errmsg\n";


            // File::putLog($msg);
            if (!in_array($_SERVER['REMOTE_ADDR'], $tADMIN_REMOTE_IP)) {
                // Mail::send(EMERGENCY_ADMIN_MAIL, PGSQL_EXEC_ERROR, "DB EXEC ERROR", $msg);
                print("テストデータ入力に失敗しました。<br>");
                exit;
            } else {
                die("<div class=\"text\">$msg</div><br>\n");
            }
        }

        $gConn = $this->conn;
        $gResult = $this->result;

        if ($count == $max_count) {
            print("テストデータ入力に成功しました。<br>");
        }

        return (new Db());
    }

    //---------------------------------------------------
    // Row取得
    //---------------------------------------------------
    // 行(Row)をとってくる(fetch)
    public function fetchRow($i = -1)
    {
        if ($i == -1) {
            // pg_fetch_array — 行を配列として取得する
            return (pg_fetch_array($this->result));
        } else {
            // PGSQL_BOTH がデフォルト設定で、これは数値添字の配列と連想配列の両方を返します。
            return (pg_fetch_array($this->result, $i, PGSQL_BOTH));
        }
    }

    public function count()
    {
        return pg_numrows($this->result);
    }

    //---------------------------------------------------
    // 結果リソース解放
    //---------------------------------------------------
    public function free()
    {
        pg_free_result($this->result);
    }

    //---------------------------------------------------
    // 変更されたレコード(タプル)の数を返す
    //---------------------------------------------------
    public function cmdTuples()
    {
        return (pg_affected_rows($this->result));
    }

    //---------------------------------------------------
    // フィールド数を返す
    //---------------------------------------------------
    public function numFields()
    {
        return (pg_num_fields($this->result));
    }

    //---------------------------------------------------
    // フィールドの名前を返す
    //---------------------------------------------------
    public function getFieldName($i)
    {
        return (pg_field_name($this->result, $i));
    }

    //---------------------------------------------------
    // フィールド番号に対応する型名を返す
    //---------------------------------------------------
    public function getFieldType($i)
    {
        return (pg_field_type($this->result, $i));
    }

    //---------------------------------------------------
    // 指定したフィールドの内部記憶領域におけるサイズを返す
    //---------------------------------------------------
    public function getFieldSize($i)
    {
        return (pg_field_size($this->result, $i));
    }

    //---------------------------------------------------
    // 次シーケンス番号を取得
    //---------------------------------------------------
    public function nextval($seqName)
    {
        $sSql = "SELECT nextval('$seqName');";
        var_dump($seqName);
        $res = $this->query($sSql);
        $aRow = $res->fetchRow();
        $res->free();

        return $aRow[nextval];
    }

    //---------------------------------------------------
    // 直近のオブジェクトIDを返す
    //---------------------------------------------------
    public function getLastOid()
    {
        return (pg_last_oid($this->result));
    }
}
