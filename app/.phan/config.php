<?php

/**
 * This configuration will be read and overlaid on top of the
 * default configuration. Command line arguments will be applied
 * after this file is read.
 */
return [
    // 下位互換性チェック。これは遅いです
    'backward_compatibility_checks' => false,

    // 親のメソッドを使用して、その署名が親と互換性があるかチェック 分析にかなりの時間
    'analyze_signature_compatibility' => false,

    // 報告する最小重大度レベル。成熟したコードは値を上げる 最大10
    'minimum_severity' => 0,

    // 不足しているプロパティの検査
    'allow_missing_properties' => true,

    // nullを配列のような型としてキャスト出来るようにする
    'null_casts_as_array' => true,

    // 配列のような型をnullにキャストできるようにする。
    'array_casts_as_null' => true,

    // 有効な場合、スカラー（int、float、bool、true、false、string、null）彼らはお互いにキャストできるかのように扱われます
    'scalar_implicit_cast' => true,

    //  これにエントリがある場合、スカラー（int、float、bool、true、false、string、null）列挙されたキャストを実行することが許可される。
    // E.g. ['int' => ['float', 'string'], 'float' => ['int'], 'string' => ['int'], 'null' => ['string']]
    'scalar_implicit_partial' => [],

    // 真の場合は、一見して宣言されていない変数スコープは無視されます
    'ignore_undeclared_variables_in_global_scope' => true,

    // 問題が報告されないようにするためのブラックリスト
    'suppress_issue_types' => [
        'PhanUndeclaredClassMethod',
        'PhanUnreferencedMethod',
        'PhanUndeclaredExtendedClass',
        'PhanUndeclaredTypeParameter',
        'PhanUndeclaredClassCatch',
        'PhanUndeclaredClass',
        'PhanUndeclaredClassConstant',
        'PhanUndeclaredStaticMethod',
        'PhanUndeclaredMethod',
        'PhanUnreferencedProperty',
        'PhanUndeclaredTypeProperty',
        'PhanTypeMismatchProperty',
        'PhanUndeclaredStaticProperty',
        'PhanUnreferencedClass',
        'PhanParamSpecial1',
        'PhanParamTooMany',
        'PhanUndeclaredConstant',
        'PhanUndeclaredVariableDim'
    ],

    // 検査対象ディレクトリ
    'directory_list' => [
        'htdocs/',
        'vendor/'
    ],

    // 検査除外ディレクトリ
    "exclude_analysis_directory_list" => [
        'vendor/',
    ],
    // 拡張子 (e.g. php, html, htm)
    'analyzed_file_extensions' => [
        'php',
    ],
];
