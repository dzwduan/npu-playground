# 代码片段0
def basicMatmulTiling_qkc(X, Y, QU, KU, CU, QTS, KTS, CTS):
    assert len(X.shape) == len(Y.shape) and len(X.shape) == 2
    assert X.shape[1] == Y.shape[0]
    Q, C = X.shape
    _, K = Y.shape
    QT, CT, KT = math.ceil(Q / QU), math.ceil(C / CU), math.ceil(K / KU)
    Z = np.zeros((Q, K))
    pe_num = QTS * KTS * CTS
    pe_inst_list = {_: [] for _ in range(pe_num)}
    X_pe, Y_pe, Z_pe = np.zeros((pe_num, QU, CU)), np.zeros((pe_num, CU, KU)), np.zeros((pe_num, QU, KU))
    QTT, CTT, KTT = math.ceil(QT / QTS), math.ceil(CT / CTS), math.ceil(KT / KTS)
    for qts in range(QTS):
        for kts in range(KTS):
            for qtt in range(QTT):
                for ktt in range(KTT):
                    qt = qtt * QTS + qts
                    kt = ktt * KTS + kts
                    q_start = qt * QU
                    q_end = min(q_start + QU, Q)
                    k_start = kt * KU
                    k_end = min(k_start + KU, K)
                    reduce_group_id = qts * KTS + kts
                    for cts in range(CTS):
                        pe_id = reduce_group_id * CTS + cts
                        for ctt in range(CTT):
                            ct = ctt * CTS + cts
                            if qt < QT and kt < KT and ct < CT:
                                c_start = ct * CU
                                c_end = min(c_start + CU, C)
                                pe_inst_list[pe_id].append(f"X[{q_start}:{q_end}, {c_start}:{c_end}]")
                                pe_inst_list[pe_id].append(f"Y[{c_start}:{c_end}, {k_start}:{k_end}]")
                    pe_inst_list[reduce_group_id * CTS].append(f"Z[{q_start}:{q_end}, {k_start}:{k_end}]")
    return Z